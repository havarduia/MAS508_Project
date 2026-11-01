function T = analyse_driver(t, X, U, active)
% ANALYSE_DRIVER  Actuator speed for each constant-voltage step of Driver_test.slx.
%   T = analyse_driver(t, X, U, active)  - time [s], payload X [m], applied U [V],
%       'step active' flag. Rig:
%   ds = load('rig_driver_run1.mat').data; g = @(n) ds.getElement(n).Values;
%   X = g('X [m]'); analyse_driver(X.Time, squeeze(X.Data), squeeze(g('U applied').Data), squeeze(g('step active').Data))
%
% While the actuator moves at constant speed v, the payload follows through the
% spring and swings around it at wn = sqrt(ks/ml): X = x0 + v*t + a*cos(wn t) + b*sin(wn t).
% Least squares on that (wn known) gives v; a plain line fit is biased by the swing.
% Compared with the linear model: speed = kv*(U - vBias)/Ke.
[~, p] = plant_model();
vBias = 0.3;
wn = sqrt(p.ks/p.ml);
on = active(:) > 0.5;
starts = find(diff([0; on]) == 1); stops = find(diff([on; 0]) == -1);
n = numel(starts);
[Ustep, dur, speed, model] = deal(zeros(n, 1));
for k = 1:n
  i = starts(k):stops(k);
  dur(k) = t(i(end)) - t(i(1));
  j = i(t(i) - t(i(1)) >= 0.03);                     % skip the electrical/back-emf transient
  tau = t(j) - t(j(1));
  c = [ones(size(tau)) tau cos(wn*tau) sin(wn*tau)] \ X(j);
  Ustep(k) = mean(U(i)); speed(k) = 1e3*c(2);
  model(k) = 1e3*p.kv*(Ustep(k) - vBias)/p.Ke;
end
T = table(Ustep, dur, speed, model, 'VariableNames', {'U_V', 'step_s', 'speed_mm_s', 'model_mm_s'});
T = sortrows(T, 'U_V');
disp(T);
if nargout == 0
  figure('Name', 'Driver map');
  plot(T.U_V, T.speed_mm_s, 'o-', T.U_V, T.model_mm_s, '--'); grid on;
  xlabel('U total [V]'); ylabel('actuator speed [mm/s]');
  legend('measured', 'linear model', 'Location', 'best');
  title('Voltage to speed through the motor driver');
  clear T
end
end
