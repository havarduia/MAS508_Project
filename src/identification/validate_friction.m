function [T, sim] = validate_friction()
% VALIDATE_FRICTION  Open-loop pulse runs against the linear model and friction_plant.
% All runs: +1 V for 0.3 s at t = 2 s from rest at the bottom stop. They differ in the voltage
% before/after it: pulse_run2/3/4 rest at 0 V and hold 0 / 0.3 / 0.19 V from t = 2 s,
% last_run sat at 0.3 V throughout. friction_plant's tBreak is fitted on pulse_run3 only.
%   validate_friction()  prints the table;  T = validate_friction()  returns it
%   [T, sim] = ...       also returns the time series per run (for report_figures)
runs = {'pulse_run2.mat', 0, 2; 'pulse_run4.mat', 0.19, 2; 'pulse_run3.mat', 0.30, 2; 'last_run.mat', 0.30, 0};
ctrl = load('controller_gains_v3a.mat'); ctrl.vBias = 0;   % open loop: controller bypassed
pl = friction_plant();
lin = plant_model(1, 0.99, 0.018);
n = size(runs, 1);
[hold, measMean, measAmp, linMean, fricMean, fricAmp, rmsLin, rmsFric] = deal(zeros(n, 1));
sim = struct('run', runs(:, 1), 't', [], 'x', [], 'xLin', [], 'xFric', []);
for r = 1:n
  [t, U, x] = loadPulse(runs{r, 1});
  xl = 1e3*lsim(lin, U - runs{r, 2}*(t >= runs{r, 3}), t);   % linear model sees the 1 V pulse only
  xf = simFric(pl, ctrl, t, U);
  k = t > 5; w = t > 1.9;
  hold(r) = runs{r, 2};
  measMean(r) = mean(x(k)); linMean(r) = mean(xl(k)); fricMean(r) = mean(xf(k));
  measAmp(r) = amp(x(k)); fricAmp(r) = amp(xf(k));
  rmsLin(r) = rms(x(w) - xl(w)); rmsFric(r) = rms(x(w) - xf(w));
  [sim(r).t, sim(r).x, sim(r).xLin, sim(r).xFric] = deal(t, x, xl, xf);
end
T = table(string(runs(:, 1)), hold, measMean, linMean, fricMean, measAmp, fricAmp, rmsLin, rmsFric, ...
  'VariableNames', {'run', 'hold_V', 'meas_mm', 'linear_mm', 'friction_mm', 'meas_ring_mm', ...
  'friction_ring_mm', 'rms_linear_mm', 'rms_friction_mm'});
if nargout == 0, disp(T); clear T; end
end

function [t, U, x] = loadPulse(file)
if strcmp(file, 'last_run.mat')
  s = load(file); t = s.u(:, 1); U = s.u(:, 2); x = 1e3*s.X_m_(:, 2);
else
  d = load(file).data; u = d.getElement(1).Values; X = d.get('X [m]').Values;   % two signals are named 'u'
  t = u.Time; U = double(u.Data(:)); x = 1e3*double(X.Data(:));
end
t = t - t(1); x = x - mean(x(t < 1.9));
end

function x = simFric(pl, ctrl, t, U)
% simulate_loop runs whole 6 s blocks at ctrl.Ts: pad the logged voltage, cut back to t
nb = ceil(t(end)/6);
tt = (0:ctrl.Ts:6*nb)';
Uo = interp1(t, U, tt, 'previous', U(end));
o = simulate_loop(pl, ctrl, zeros(1, nb), struct('sigX', 0, 'push', false, 'uOpen', Uo));
x = interp1(o.t, 1e3*o.xm, t);   % what the sensor reports, like the logged X
end

function a = amp(x)
a = (prctile(x, 99) - prctile(x, 1))/2;
end
