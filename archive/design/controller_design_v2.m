%% Controller design v2 (6-state, kv 0.66; rig_v2_run1: hold 0.75 mm). Superseded by controller_design.m (v3)
% Course references: integral control L3d (example4_integralcontrol.m),
% LQR + Bryson's rule L3g, Kalman observer / separation principle L3e-L3h.
% v1 (controller_design_v1.m) used the 5-state model. On the rig it oscillated at
% 3-6 Hz (runs A-C): the position sensor lag (10.6 ms) and the faster actuator
% (tauM 18 ms, not 31 ms) took most of the damping of its ~4 Hz closed-loop mode.
% v2 designs on the model with both, and the weights are picked for the worst-case
% damping over tauM 12-31 ms, eta 0.66, gain x0.5-x2 and extra delay (robustness section).
clearvars; close all; clc;

Ts   = 1e-4;          % Speedgoat sample time [s] (10 kHz)
vBias = 0.3;          % holding voltage when the inverse driver map is off (useInv = 0) [V]
vMax  = 5;            % interface limit on the total voltage [V]
sigX  = 22e-6;        % sensor noise std [m], sample-to-sample on last_run.mat rest data
tauM  = 0.018;        % actuator time constant from chirp run 4 + video [s]
tauS  = 0.0106;       % sensor lag: Balluff -3 dB at 15 Hz, = our 3.5 ms lag + 7 ms hold delay [s]

[sys, p] = plant_model(1, 0.66, tauM, tauS);   % states [i y ydot x xdot xs], output xs
[A, B, C, ~] = ssdata(sys);
n = size(A, 1);

%% Controllability and observability (Hautus, ctrb_calc.m from canvas)
e = eig(A);
ctrb_calc;

%% Augmented plant with the integral of the tracking error, xN' = r - xs
% Integral action instead of a prefilter: a prefilter N = 1/dcgain relies on
% the model gain, which was 34 % off before kv was identified. The integrator
% removes steady-state error whatever the true gain, bias or load force is.
% It integrates the measured position, as the Simulink model does.
Ai = [A zeros(n, 1); -C 0];
Bi = [B; 0];

%% LQR weights from Bryson's rule: q_ii = 1/(max acceptable value)^2
% Grid search over xMax, xdMax, xNMax, R and qF on the linear worst-case damping
% (tauM 12-31 ms, eta 0.66, kv x0.5 and x2, +10 ms delay), then the top 30 in the
% nonlinear sim (sensor hold, driver map + inverse). The best linear-damping sets
% have only 3 dB gain margin and hunt in the driver's stuck band. This set is the
% best in the nonlinear sim (hold std 0.09-0.19 mm) with worst-case damping 0.16.
iMax   = 5;        % current [A]
yMax   = 0.025;    % actuator position = stroke [m]
ydMax  = 0.15;     % actuator velocity [m/s] (about the 5 V back-emf limit)
xMax   = 0.004;    % payload position error [m]
xdMax  = 0.05;     % payload velocity [m/s]
xsMax  = 1e3;      % sensor state: not weighted, x already is
xNMax  = 0.0005;    % integrated position error [m s]
Q = diag(1 ./ [iMax yMax ydMax xMax xdMax xsMax xNMax].^2);
R = 1 / vMax^2;

%% Kalman observer for the 6 plant states (only xs is measured)
% Process noise: input voltage noise and a force on the payload (disturbance).
% A large assumed force (2 N) makes the observer fast, which the grid search
% preferred: the observer adds less phase lag at the crossover.
G  = [B, [0; 0; 0; 0; 1/p.ml; 0]];
qv = 1;            % voltage process noise std [V]
qF = 2;            % payload force process noise std [N]
Rn = sigX^2;       % measured sensor noise [m^2]

Kaug = lqr(Ai, Bi, Q, R);
K  = Kaug(1:n);          % u = -K*xhat + Ke*xN  (course notation)
Ke = -Kaug(n + 1);
[~, Lobs] = kalman(ss(A, [B G], C, 0), diag([qv^2, qF^2]), Rn);
disp('Closed-loop controller poles:'); disp(eig(Ai - Bi*Kaug));
disp('Observer poles:');               disp(eig(A - Lobs*C));
save('controller_gains_v2.mat', 'K', 'Ke', 'Lobs', 'A', 'B', 'C', 'Ts', 'vBias', 'vMax');

%% Robustness: margins and worst-case damping, v2 against v1
% Controller from measured x to u: observer + integrator, u = -K*xhat + Ke*xN
lqgCtrl = @(g) ss([g.A - g.B*g.K - g.Lobs*g.C, g.B*g.Ke; zeros(1, size(g.A, 1)) 0], ...
                  [g.Lobs; -1], [-g.K g.Ke], 0);
% eta, tauM [s], extra delay on the voltage [s]
tests = [1 .018 0; 1 .012 0; 1 .031 0; .66 .018 0; 1 .018 .010; 1 .018 .020; .66 .031 .010];
sets = {'v2', 'controller_gains_v2.mat'; 'v1', 'controller_gains_v1.mat'; 'soft v1', 'controller_gains_soft_v1.mat'};
fprintf('\n%-8s %6s %6s %7s | least damping: nom, tau 12, tau 31, eta .66, +10 ms, +20 ms, eta .66 tau 31 +10 ms\n', ...
  'gains', 'GM dB', 'PM', 'DM ms');
for s = 1:size(sets, 1)
  ctl = lqgCtrl(load(sets{s, 2}));
  [gm, pm, ~, wc] = margin(-ctl*sys);
  z = zeros(1, size(tests, 1));
  for t = 1:size(tests, 1)
    P = plant_model(tests(t, 1), 0.66, tests(t, 2), tauS);
    if tests(t, 3) > 0, P = ss(P*pade(tf(1, 1, 'InputDelay', tests(t, 3)), 3)); end
    ev = eig(feedback(P, ctl, +1));
    ev = ev(abs(ev) > 1e-6);
    z(t) = min(-real(ev)./abs(ev));
  end
  fprintf('%-8s %6.1f %6.1f %7.1f | %s\n', sets{s, 1}, 20*log10(gm), pm, 1e3*pm*pi/180/wc, sprintf('%6.2f', z));
end

%% Simulation on the rig-like plant: sensor hold + lag, measured driver map, inverse map on
ctrl = load('controller_gains_v2.mat');
ctrl.vBias = 0; ctrl.inv = driver_map();   % as Project_Controller with useInv = 1

% name, eta, tauM [s], extra delay [s]; same K and L for every case
cases = {
  'nominal (tauM 18 ms)',       1.00, 0.018, 0
  'tauM 12 ms',                 1.00, 0.012, 0
  'tauM 31 ms (datasheet)',     1.00, 0.031, 0
  'eta 0.66',                   0.66, 0.018, 0
  '+10 ms delay',               1.00, 0.018, 0.010
};
refs = {[15 5], [20 5]};       % payload targets above x0 [mm], hold 6 s each
opts = struct('sigX', sigX, 'push', true);
rng(1);

for r = 1:numel(refs)
  figure('Name', sprintf('Reference %d -> %d mm', refs{r}));
  for c = 1:size(cases, 1)
    [plant.sys, plant.p] = plant_model(cases{c, 2}, 0.66, cases{c, 3});
    plant.dv = 0; plant.Fc = 0; plant.Fs = 0;
    plant.Tsens = 0.014; plant.tauSens = 0.0035; plant.drv = driver_map();
    plant.delay = cases{c, 4};
    out = simulate_loop(plant, ctrl, refs{r}, opts);
    report(cases{c, 1}, refs{r}, out);
    subplot(3, 1, 1); hold on; plot(out.t, 1e3*out.x);  ylabel('x - x_0 [mm]');
    subplot(3, 1, 2); hold on; plot(out.t, 1e3*out.y);  ylabel('y [mm]');
    subplot(3, 1, 3); hold on; plot(out.t, out.v);      ylabel('U driver [V]'); xlabel('t [s]');
  end
  subplot(3, 1, 1); plot(out.t, 1e3*out.r, 'k:'); legend([cases(:, 1); {'reference'}], 'Location', 'best');
  title(sprintf('LQG v2, %d -> %d mm, 1 N push at 3.5-4.5 s', refs{r}));
  for k = 1:3, subplot(3, 1, k); grid on; end
end
fprintf('\n');

%% Local functions
function report(name, refsMm, out)
tHold = 6;
fprintf('\n%-24s ', name);
for j = 1:numel(refsMm)
  idx = out.t >= (j - 1)*tHold & out.t < j*tHold;
  t = out.t(idx) - (j - 1)*tHold; x = 1e3*out.x(idx); target = refsMm(j);
  outside = find(abs(x - target) > 0.25, 1, 'last');     % settle band +-0.25 mm
  % settling is judged before the push (t < 3.5 s) on the first hold
  if j == 1, outside = find(abs(x(t < 3.5) - target) > 0.25, 1, 'last'); end
  ts = t(min(outside + 1, numel(t)));
  % first hold: error just before the push, not while recovering from it
  if j == 1, iss = t > 3.0 & t < 3.5; else, iss = t > tHold - 0.5; end
  fprintf('| %2d mm: ts %.2f s, ss err %.3f mm, hold std %.3f mm ', target, ts, ...
    mean(x(iss)) - target, std(x(iss)));
end
fprintf('| y %.1f..%.1f mm, |U| max %.2f V, U std %.2f V', 1e3*min(out.y), 1e3*max(out.y), ...
  max(abs(out.v)), std(out.v(out.t > 2*tHold - 2)));
end
