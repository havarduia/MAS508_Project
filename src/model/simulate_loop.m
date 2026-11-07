function out = simulate_loop(plant, ctrl, refsMm, opts)
% SIMULATE_LOOP  Closed loop at the Speedgoat rate, run as the real-time code runs it.
%   plant  - true plant: .sys (from plant_model), .p (its parameters),
%            .dv  holding bias error [V],
%            .Fc  Coulomb friction on the actuator [N] (0 = none),
%            .Fs  static (breakaway) friction [N]
%            .tau (optional) first-order lag on the voltage, e.g. motor driver [s]
%            .delay (optional) pure time delay on the voltage [s]
%            .Tsens, .tauSens (optional) position sensor that only updates every Tsens [s],
%                  followed by a first-order lag tauSens [s] (rig: about 14 ms and 3.5 ms)
%            .drv (optional) measured motor-driver map, see driver_map.m: total voltage U
%                  -> plant input, with separate up/down branches and a stuck band.
%                  .drv.restick (optional) true: no drive while U is back inside the stuck band,
%                  so a sliding actuator stops instead of creeping on the sliding line
%            .coast0 (optional) true: at U == 0 exactly the driver output is off, the motor
%                  carries no current and the weight back-drives the screw (pulse_run2)
%            .yMin (optional) bottom end stop of the actuator, deviation coordinates [m]
%            .tBreak (optional) time the actuator stays stuck on the end stop after the
%                  drive first exceeds the stuck band [s]
%   ctrl   - struct loaded from controller_gains.mat; optional .uFc [V] adds Coulomb
%            friction compensation uFc*tanh(uCmd/0.05) in the direction the controller pushes;
%            optional .inv applies the inverse driver map to u + vBias (as Project_Controller)
%   refsMm - payload targets above x0 [mm], held 6 s each (opts.tHold)
%   opts   - .sigX sensor noise std [m], .push true adds a 1 N push at 3.5-4.5 s (opts.tPush),
%            .tHold (optional) hold time per target [s], .tPush (optional) push window [start end] [s]
%            .uOpen (optional) open-loop voltage per sample, bypasses the controller
%            .dither (optional) [amplitude V, frequency Hz] sine added to the controller
%                  output before the limit, like the chirp block with fExc1 = fExc2
tHold = 6; if isfield(opts, 'tHold'), tHold = opts.tHold; end
tP = [3.5 4.5]; if isfield(opts, 'tPush'), tP = opts.tPush; end
Ts = ctrl.Ts; K = ctrl.K; Ke = ctrl.Ke;
t = (0:Ts:numel(refsMm)*tHold)';
N = numel(t);
r = 1e-3*refsMm(min(floor(t/tHold) + 1, numel(refsMm)))';
Fd = opts.push*1.0*(t >= tP(1) & t < tP(2));
Nff = 0;
if isfield(ctrl, 'pre'), r = filter(ctrl.pre.b, ctrl.pre.a, r); Nff = ctrl.pre.N; end

p = plant.p;
[At, Bt, Ct] = ssdata(plant.sys);          % true plant: 5 states, the sensor is modelled below
G = [0 0; 0 0; 0 1/p.Me; 0 0; 1/p.ml 0];      % [push on payload, friction on actuator]
plantD = c2d(ss(At, [Bt G], eye(5), 0), Ts);
obsD   = c2d(ss(ctrl.A - ctrl.Lobs*ctrl.C, [ctrl.B ctrl.Lobs], eye(size(ctrl.A, 1)), 0), Ts);

xt = zeros(5, 1); xh = zeros(size(ctrl.A, 1), 1); xN = 0; uLag = 0;
tau = 0; if isfield(plant, 'tau'), tau = plant.tau; end
nD = 0; if isfield(plant, 'delay'), nD = round(plant.delay/Ts); end
buf = zeros(nD, 1); iD = 1;
Tsens = 0; if isfield(plant, 'Tsens'), Tsens = plant.Tsens; tauSens = plant.tauSens; end
xHold = 0; xSens = 0; tNext = 0;
stuck = true; dirn = 0;
iW = (p.ma + p.ml)*p.g/p.Kf;   % holding current: the equilibrium the deviation states are taken around
tPush = 0;                     % time the drive has been pushing the actuator off the end stop
uLo = -ctrl.vMax - ctrl.vBias; uHi = ctrl.vMax - ctrl.vBias;   % limit applies to v + bias
if isfield(ctrl, 'inv')   % limit u + bias so the inverse map stays inside +-vMax
  uLo = ctrl.inv.gDn*(-ctrl.vMax - ctrl.inv.u0Dn) - ctrl.vBias;
  uHi = ctrl.inv.gUp*(ctrl.vMax - ctrl.inv.u0Up) - ctrl.vBias;
end
out.t = t; out.r = r; out.x = zeros(N, 1); out.y = zeros(N, 1); out.v = zeros(N, 1); out.xm = zeros(N, 1);
for k = 1:N
  if Tsens > 0
    if t(k) >= tNext, xHold = Ct*xt; tNext = tNext + Tsens; end
    xSens = xSens + Ts/tauSens*(xHold - xSens);
    yMeas = xSens + opts.sigX*randn;
  else
    yMeas = Ct*xt + opts.sigX*randn;
  end
  err = r(k) - yMeas;
  uCmd = -K*xh + Ke*xN + Nff*r(k);
  uFric = 0; if isfield(ctrl, 'uFc'), uFric = ctrl.uFc*tanh(uCmd/0.05); end
  uCmd = uCmd + uFric;
  if isfield(opts, 'dither'), uCmd = uCmd + opts.dither(1)*sin(2*pi*opts.dither(2)*t(k)); end
  u = min(max(uCmd, uLo), uHi);
  if isfield(opts, 'uOpen'), u = opts.uOpen(k); uCmd = u; end
  % anti-windup: freeze the integrator while saturated and the error would push further
  if u == uCmd || sign(Ke*err) ~= sign(uCmd)
    xN = xN + Ts*err;
  end
  xh = obsD.A*xh + obsD.B*[u - uFric; yMeas];   % applied u, minus the part spent on friction
  Ffr = friction(xt, plant, p);
  if isnan(Ffr), xt(3) = 0; Ffr = -driveForce(xt, plant, p); end   % stuck: friction cancels the drive
  Utot = u + ctrl.vBias;                       % voltage sent to the driver
  if isfield(ctrl, 'inv'), Utot = invDriver(Utot, ctrl.inv); end   % as Project_Controller
  Utot = min(max(Utot, -ctrl.vMax), ctrl.vMax);
  vIn = u;
  coast = isfield(plant, 'coast0') && plant.coast0 && Utot == 0;
  if isfield(plant, 'drv') && ~coast
    [vIn, stuck, dirn] = driver(Utot, xt(3), stuck, dirn, plant.drv);
    onStop = isfield(plant, 'yMin') && xt(2) <= plant.yMin + 1e-6;   % 1 um: the stuck force cancels only to rounding
    if onStop && isfield(plant, 'tBreak') && ~stuck && abs(xt(3)) < 1e-4
      tPush = tPush + Ts;
      if tPush < plant.tBreak, stuck = true; end   % breakaway from the end stop takes tBreak
    else
      tPush = 0;
    end
    if stuck, xt(3) = 0; Ffr = -driveForce(xt, plant, p); end
  elseif coast
    stuck = false; Ffr = 0; vIn = 0;
  end
  if nD > 0, [buf(iD), vIn] = deal(vIn, buf(iD)); iD = mod(iD, nD) + 1; end
  if tau > 0, uLag = uLag + Ts/tau*(vIn - uLag); else, uLag = vIn; end
  xt = plantD.A*xt + plantD.B*[uLag + plant.dv; Fd(k); Ffr];
  if coast, xt(1) = -iW; end   % no motor current: deviation current = minus the holding current
  if isfield(plant, 'yMin') && xt(2) < plant.yMin
    xt(2) = plant.yMin; xt(3) = max(xt(3), 0);
    if isfield(plant, 'drv') && Utot <= plant.drv.uHi, stuck = true; end   % resting on the stop
  end
  out.x(k) = xt(4); out.y(k) = xt(2); out.v(k) = Utot; out.xm(k) = yMeas;
end
end

function [v, stuck, dirn] = driver(U, yd, stuck, dirn, d)
% measured driver: stuck inside [uLo, uHi]; sliding up/down follow separate lines,
% scaled so the linear plant reproduces the measured speeds
vStick = 1e-4;
if stuck
  if U > d.uHi, stuck = false; dirn = 1; elseif U < d.uLo, stuck = false; dirn = -1; end
elseif abs(yd) > vStick
  dirn = sign(yd);
elseif U >= d.uLo && U <= d.uHi
  stuck = true;
end
if dirn >= 0, v = d.gUp*(U - d.u0Up); else, v = d.gDn*(U - d.u0Dn); end
if isfield(d, 'restick') && d.restick && U >= d.uLo && U <= d.uHi, v = 0; end
end

function U = invDriver(w, d)
% inverse of the sliding lines: command w [V] -> driver voltage. Optional d.iUp / d.iDn
% replace the zero-speed offsets, e.g. with the stuck-band edges (dead-zone inverse)
up = d.u0Up; dn = d.u0Dn;
if isfield(d, 'iUp'), up = d.iUp; dn = d.iDn; end
if w >= 0, U = up + w/d.gUp; else, U = dn + w/d.gDn; end
end

function F = driveForce(xt, plant, p)
% net force on the actuator from motor, spring and damper (gravity is in the equilibrium)
F = p.Kf*xt(1) - p.ks*(xt(2) - xt(4)) - p.bs*(xt(3) - xt(5));
end

function Ffr = friction(xt, plant, p)
% Coulomb friction while sliding; NaN = stuck (static friction holds the stage)
Ffr = 0;
if plant.Fc == 0, return; end
vStick = 1e-4;   % [m/s] below this the stage counts as stopped
F = driveForce(xt, plant, p);
if abs(xt(3)) < vStick
  if abs(F) <= plant.Fs
    Ffr = NaN;
  else
    Ffr = -plant.Fc*sign(F);
  end
else
  Ffr = -plant.Fc*sign(xt(3));
end
end
