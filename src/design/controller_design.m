%% Controller design v3: LQR with integral action + Kalman observer (LQG) on the identified plant
% Course references: modelling L2a-c, identification L2d, integral control L3d
% (example4_integralcontrol.m), observer rule of thumb L3e, LQR + Bryson's rule L3g,
% Kalman / LQG L3h, gain and phase margins L5.
%
% Why v3: on the rig, v1 oscillated at ~6 Hz (U) and wandered +-1 mm while holding.
% With the identified actuator gain (1.5x the datasheet model) the linear model predicts
% exactly that: v1's least-damped mode is zeta 0.09 at 6.5 Hz, gain margin 2.2 dB, and the
% soft v1 gains are unstable with 5 ms extra delay (run C's limit cycle).
% v2 (more margin, slower) wandered more (0.75 mm): with a slow loop the integrator hunts
% in the motor driver's stuck band (measured, driver_map.m). v3 trades the two off.
%
% Selection (two variants, each a plain LQG design):
%   1) linearly stable over the whole uncertainty range: actuator gain x1-x2 of the
%      datasheet model, tauM 12-31 ms, eta 0.66, +5 ms delay
%   2) estimated settling time 4/sigma <= 2 s, observer poles >= 2x faster than the
%      dominant controller poles (L3e)
%   3) lowest hold error in a simulation built from measured parts only: identified
%      gain, sensor hold + lag, measured driver map, measured 0.6 V holding voltage
clearvars; close all; clc;

Ts   = 1e-4;          % Speedgoat sample time [s] (10 kHz)
vMax  = 5;            % interface limit on the total voltage [V]
vBias = 0.6;          % holding voltage = equilibrium input (L2b/L2c), measured in every rig run [V]
sigX  = 22e-6;        % sensor noise std [m], sample-to-sample on last_run.mat rest data
kv    = 0.99;         % input gain: 1.5x the datasheet model (0.66), see below
tauM  = 0.018;        % actuator time constant, frequency response of chirp run 4 [s]
tauS  = 0.0106;       % sensor lag: Balluff -3 dB at 15 Hz = our 3.5 ms lag + 7 ms hold delay [s]
% kv: closed-loop video FRFs gave 1.5-2x the model gain at 5-11 Hz, and with 1.5x the
% model reproduces the rig's 6 Hz oscillation of v1 and run C's instability (robustness section).

[sys, p] = plant_model(1, kv, tauM, tauS);   % states [i y ydot x xdot xs], output xs
[A, B, C, ~] = ssdata(sys);
n = size(A, 1);

%% Controllability and observability (Hautus, ctrb_calc.m from canvas)
e = eig(A);
ctrb_calc;

%% Augmented plant with the integral of the tracking error, xN' = r - xs (L3d)
% Integral action removes steady-state error whatever the true gain, bias or load is.
% It integrates the measured position, as the Simulink model does.
Ai = [A zeros(n, 1); -C 0];
Bi = [B; 0];

%% Two weight sets from Bryson's rule, q_ii = 1/(max acceptable value)^2, r = 1/u_max^2
% Fixed in both: iMax 5 A (motor rated 5.14 A), yMax 25 mm (stroke), ydMax 0.15 m/s
% (back-emf at 5 V), sensor state xs not weighted (x already is).
% v3a: loose payload position (8 mm), firm payload velocity (20 mm/s), 1 V of effort
% v3b: tight payload position (1 mm), payload velocity 10 mm/s, 2.5 V of effort
%                 xMax    xdMax  xNMax   uMax  qF   qv
variants = {'v3a', 0.008, 0.02,  0.001,  5,    1,   3
            'v3b', 0.001, 0.01,  0.0005, 2.5,  1,   1};
G  = [B, [0; 0; 0; 0; 1/p.ml; 0]];   % process noise enters as voltage and payload force
Rn = sigX^2;                          % measured sensor noise [m^2]

for v = 1:size(variants, 1)
  [name, xMax, xdMax, xNMax, uMax, qF, qv] = variants{v, :};
  Q = diag(1 ./ [5 0.025 0.15 xMax xdMax 1e3 xNMax].^2);
  R = 1 / uMax^2;
  Kaug = lqr(Ai, Bi, Q, R);
  K  = Kaug(1:n);          % u = -K*xhat + Ke*xN  (course notation)
  Ke = -Kaug(n + 1);
  % Kalman: qv = voltage process noise std [V] (gain uncertainty x1-x2 on ~1-3 V commands),
  % qF = payload force std [N] (the 1 N push in the spec)
  [~, Lobs] = kalman(ss(A, [B G], C, 0), diag([qv^2, qF^2]), Rn);
  ec = eig(Ai - Bi*Kaug); eo = eig(A - Lobs*C);
  fprintf('\n%s: controller poles', name); fprintf(' %.1f%+.1fi', [real(ec) imag(ec)]');
  fprintf('\n%s: observer poles  ', name);  fprintf(' %.1f%+.1fi', [real(eo) imag(eo)]');
  fprintf('\n%s: slowest observer pole / dominant controller pole = %.1f (L3e: 2-5)\n', ...
    name, min(-real(eo))/min(-real(ec)));
  save(fullfile(fileparts(mfilename('fullpath')), '..', '..', 'data', 'gains', ['controller_gains_' name '.mat']), ...
    'K', 'Ke', 'Lobs', 'A', 'B', 'C', 'Ts', 'vBias', 'vMax');
end

%% Robustness: margins and least damping over the uncertainty range, v3 against older sets
lqgCtrl = @(g) ss([g.A - g.B*g.K - g.Lobs*g.C, g.B*g.Ke; zeros(1, size(g.A, 1)) 0], ...
                  [g.Lobs; -1], [-g.K g.Ke], 0);
% eta, kv, tauM [s], extra delay [s]
tests = [1 .66 .018 0; 1 .99 .018 0; 1 1.32 .018 0; 1 .99 .012 0; 1 .99 .031 0; .66 .99 .018 0;
         1 .99 .018 .005; 1 1.32 .018 .005; 1 1.32 .012 .005; .66 .66 .031 .005];
sets = {'v3a', 'v3b', 'v2', 'v1', 'soft_v1'};
fprintf('\n%-8s %6s %6s | least damping over %d cases (gain x1-x2, tauM 12-31 ms, eta .66, +5 ms)\n', ...
  'gains', 'GM dB', 'PM', size(tests, 1));
for s = 1:numel(sets)
  ctl = lqgCtrl(load(['controller_gains_' sets{s} '.mat']));
  [gm, pm] = margin(-ctl*sys);     % at the identified plant
  z = zeros(1, size(tests, 1));
  for t = 1:size(tests, 1)
    P = plant_model(tests(t, 1), tests(t, 2), tests(t, 3), tauS);
    if tests(t, 4) > 0, P = ss(P*pade(tf(1, 1, 'InputDelay', tests(t, 4)), 3)); end
    ev = eig(feedback(P, ctl, +1));
    ev = ev(abs(ev) > 1e-6);
    z(t) = min(-real(ev)./abs(ev));
  end
  fprintf('%-8s %6.1f %6.1f | min %5.2f | %s\n', sets{s}, 20*log10(gm), pm, min(z), sprintf('%6.2f', z));
end

%% Simulation from measured parts: identified gain, sensor hold + lag, driver map, 0.6 V hold
% 1 N push at 3.5-4.5 s; plant gain x1, x1.5 (identified) and x2
refs = {[15 5], [20 5]};
for v = 1:size(variants, 1)
  ctrl = load(['controller_gains_' variants{v, 1} '.mat']);
  for r = 1:numel(refs)
    figure('Name', sprintf('%s, %d -> %d mm', variants{v, 1}, refs{r}));
    for kvTrue = [0.66 0.99 1.32]
      [plant.sys, plant.p] = plant_model(1, kvTrue, tauM);
      plant.dv = -0.5;          % plant needs 0.6 V at the driver to hold: drv(0.6 V) = 0.5
      plant.Fc = 0; plant.Fs = 0;
      plant.Tsens = 0.014; plant.tauSens = 0.0035; plant.drv = driver_map();
      rng(1); out = simulate_loop(plant, ctrl, refs{r}, struct('sigX', sigX, 'push', true));
      report(sprintf('%s, plant kv %.2f', variants{v, 1}, kvTrue), refs{r}, out);
      subplot(3, 1, 1); hold on; plot(out.t, 1e3*out.x);  ylabel('x - x_0 [mm]');
      subplot(3, 1, 2); hold on; plot(out.t, 1e3*out.y);  ylabel('y [mm]');
      subplot(3, 1, 3); hold on; plot(out.t, out.v);      ylabel('U [V]'); xlabel('t [s]');
    end
    subplot(3, 1, 1); plot(out.t, 1e3*out.r, 'k:'); legend('kv 0.66', 'kv 0.99', 'kv 1.32', 'reference');
    title(sprintf('LQG %s, %d -> %d mm, 1 N push at 3.5-4.5 s', variants{v, 1}, refs{r}));
    for k = 1:3, subplot(3, 1, k); grid on; end
  end
end
fprintf('\n');

%% Local functions
function report(name, refsMm, out)
tHold = 6;
fprintf('\n%-20s ', name);
for j = 1:numel(refsMm)
  idx = out.t >= (j - 1)*tHold & out.t < j*tHold;
  t = out.t(idx) - (j - 1)*tHold; x = 1e3*out.x(idx); target = refsMm(j);
  outside = find(abs(x - target) > 0.25, 1, 'last');     % settle band +-0.25 mm
  % settling is judged before the push (t < 3.5 s) on the first hold
  if j == 1, outside = find(abs(x(t < 3.5) - target) > 0.25, 1, 'last'); end
  ts = t(min(outside + 1, numel(t)));
  % first hold: error just before the push, not while recovering from it
  if j == 1, iss = t > 3.0 & t < 3.5; else, iss = t > tHold - 0.5; end
  fprintf('| %2d mm: ts %.2f s, ss err %+.3f mm, std %.3f mm ', target, ts, ...
    mean(x(iss)) - target, std(x(iss)));
end
fprintf('| y %.1f..%.1f mm, |U| max %.2f V', 1e3*min(out.y), 1e3*max(out.y), max(abs(out.v)));
end
