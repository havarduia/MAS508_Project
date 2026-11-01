%% Controller design v1 (5-state model, used on rig runs A-C). Superseded by controller_design.m
% Course references: integral control L3d (example4_integralcontrol.m),
% LQR + Bryson's rule L3g, Kalman observer / separation principle L3e-L3h.
clearvars -except gainSet; close all; clc;   % gainSet = 'soft' simulates the quieter set

Ts   = 1e-4;          % Speedgoat sample time [s] (10 kHz)
vBias = 0.3;          % holding voltage added outside the controller [V]
vMax  = 5;            % interface limit on the total voltage [V]
sigX  = 22e-6;        % sensor noise std [m], sample-to-sample on last_run.mat rest data

[sys, p] = plant_model();          % nominal design model: eta = 1, kv = 0.66
[A, B, C, ~] = ssdata(sys);
n = size(A, 1);

%% Controllability and observability (Hautus, ctrb_calc.m from canvas)
e = eig(A);
ctrb_calc;

%% Augmented plant with the integral of the tracking error, xN' = r - x
% Integral action instead of a prefilter: a prefilter N = 1/dcgain relies on
% the model gain, which was 34 % off before kv was identified. The integrator
% removes steady-state error whatever the true gain, bias or load force is.
Ai = [A zeros(n, 1); -C 0];
Bi = [B; 0];

%% LQR weights from Bryson's rule: q_ii = 1/(max acceptable value)^2
% The payload velocity weight is what adds damping to the 2.56 Hz mode,
% which has almost none of its own (zeta = 0.00026).
iMax   = 5;        % current [A]
yMax   = 0.025;    % actuator position = stroke [m]
ydMax  = 0.15;     % actuator velocity [m/s] (about the 5 V back-emf limit)
xMax   = 0.002;    % payload position error [m]
xdMax  = 0.02;     % payload velocity [m/s]
xNMax  = 0.0005;   % integrated position error [m s]
Q = diag(1 ./ [iMax yMax ydMax xMax xdMax xNMax].^2);
R = 1 / vMax^2;

%% Kalman observer for the 5 plant states (only x is measured)
% Process noise: input voltage noise and a force on the payload (disturbance).
G  = [B, [0; 0; 0; 0; 1/p.ml]];
qv = 1;                      % voltage process noise std [V]. 0.1 V gave an observer
                             % pole at -0.78 rad/s, far slower than the controller
Rn = sigX^2;                 % measured sensor noise [m^2]

[K, Ke, Lobs] = designGains(Ai, Bi, Q, R, A, B, C, G, qv, 0.5, Rn);
save('controller_gains_v1.mat', 'K', 'Ke', 'Lobs', 'A', 'B', 'C', 'Ts', 'vBias', 'vMax');

% Quieter set for the rig (gainSet = 'soft'): voltage 10x more expensive in the
% LQR cost and a smaller assumed payload force (0.1 N). In simulation: same
% settling time (the integrator pole sets it), 3x less voltage noise, and the
% slowest observer pole moves from -7.9 to -31 rad/s (5x rule from L3d now met).
[K, Ke, Lobs] = designGains(Ai, Bi, Q, 10*R, A, B, C, G, qv, 0.1, Rn);
save('controller_gains_soft_v1.mat', 'K', 'Ke', 'Lobs', 'A', 'B', 'C', 'Ts', 'vBias', 'vMax');

%% Simulation: nominal plant plus robustness variants, same K and L
if exist('gainSet', 'var') && strcmp(gainSet, 'soft'), ctrl = load('controller_gains_soft_v1.mat');
else, ctrl = load('controller_gains_v1.mat'); end

% name, eta, kv, holding bias error [V]; same K and L for every case
cases = {
  'nominal (eta 1, kv 0.66)',   1.00, 0.66, 0
  'kv 1.0 (no friction loss)',  1.00, 1.00, 0
  'kv 0.5 (more friction)',     1.00, 0.50, 0
  'eta 0.66',                   0.66, 0.66, 0
  'bias error +0.15 V',         1.00, 0.66, 0.15
};
refs = {[15 5], [20 5]};       % payload targets above x0 [mm], hold 6 s each
opts = struct('sigX', sigX, 'push', true);

for r = 1:numel(refs)
  figure('Name', sprintf('Reference %d -> %d mm', refs{r}));
  for c = 1:size(cases, 1)
    [plant.sys, plant.p] = plant_model(cases{c, 2}, cases{c, 3});
    plant.dv = cases{c, 4}; plant.Fc = 0; plant.Fs = 0;
    out = simulate_loop(plant, ctrl, refs{r}, opts);
    report(cases{c, 1}, refs{r}, out);
    subplot(3, 1, 1); hold on; plot(out.t, 1e3*out.x);  ylabel('x - x_0 [mm]');
    subplot(3, 1, 2); hold on; plot(out.t, 1e3*out.y);  ylabel('y [mm]');
    subplot(3, 1, 3); hold on; plot(out.t, out.v);      ylabel('v total [V]'); xlabel('t [s]');
  end
  subplot(3, 1, 1); plot(out.t, 1e3*out.r, 'k:'); legend([cases(:, 1); {'reference'}], 'Location', 'best');
  title(sprintf('LQR + integral + Kalman, %d -> %d mm, 1 N push at 3.5-4.5 s', refs{r}));
  for k = 1:3, subplot(3, 1, k); grid on; end
end

%% Local functions
function report(name, refsMm, out)
tHold = 6;
fprintf('\n%-28s ', name);
for j = 1:numel(refsMm)
  idx = out.t >= (j - 1)*tHold & out.t < j*tHold;
  t = out.t(idx) - (j - 1)*tHold; x = 1e3*out.x(idx); target = refsMm(j);
  outside = find(abs(x - target) > 0.25, 1, 'last');     % settle band +-0.25 mm
  % settling is judged before the push (t < 3.5 s) on the first hold
  if j == 1, outside = find(abs(x(t < 3.5) - target) > 0.25, 1, 'last'); end
  ts = t(min(outside + 1, numel(t)));
  % first hold: error just before the push, not while recovering from it
  if j == 1, iss = t > 3.0 & t < 3.5; else, iss = t > tHold - 0.5; end
  fprintf('| %2d mm: ts %.2f s, ss err %.3f mm ', target, ts, mean(x(iss)) - target);
end
fprintf('| y %.1f..%.1f mm, |v| max %.2f V', 1e3*min(out.y), 1e3*max(out.y), max(abs(out.v)));
end

function [K, Ke, Lobs] = designGains(Ai, Bi, Q, R, A, B, C, G, qv, qF, Rn)
n = size(A, 1);
Kaug = lqr(Ai, Bi, Q, R);
K  = Kaug(1:n);          % u = -K*xhat + Ke*xN  (course notation)
Ke = -Kaug(n + 1);
Qn = diag([qv^2, qF^2]);    % process noise [V^2, N^2]
[~, Lobs] = kalman(ss(A, [B G], C, 0), Qn, Rn);
fprintf('\nR = %.3g, qv = %.2g V, qF = %.2g N\n', R, qv, qF);
disp('Closed-loop controller poles:'); disp(eig(Ai - Bi*Kaug));
disp('Observer poles:');               disp(eig(A - Lobs*C));
end
