%% Friction check: does stick-slip friction explain the rig behaviour?
% 1) Identify Coulomb friction Fc from the open-loop pulse (validate_step kEff = 0.657):
%    at steady speed the motor current only has to beat friction, i = Fc/Kf, which
%    costs R*i volts, so ydot = (v - R*Fc/Kf)/Ke. Travel ratio kEff = 1 - R*Fc/(Kf*v).
% 2) Re-run the closed loop on a plant with kv = 1 plus that friction and compare
%    the hunting with rig_15_5_run1.mat (std 0.3-0.57 mm, ~1.7 Hz).
clear; close all; clc;
ctrl = load('controller_gains_v1.mat');
[sys1, p1] = plant_model(1.0, 1.0);          % no lumped gain, friction modelled explicitly
kEff = 0.657; vPulse = 1;
Fc = (1 - kEff)*vPulse*p1.Kf/p1.R;
fprintf('Coulomb friction from the pulse test: Fc = %.1f N at the nut\n', Fc);

%% 1) open-loop pulse: kv = 1 + friction should give the measured 8.73 mm
t = (0:ctrl.Ts:12)';
plant = struct('sys', sys1, 'p', p1, 'dv', 0, 'Fc', Fc, 'Fs', 1.2*Fc);
opts = struct('sigX', 0, 'push', false, 'uOpen', vPulse*(t >= 2 & t < 2.3));
out = simulate_loop(plant, ctrl, [0 0], opts);
fprintf('open-loop pulse travel: %.2f mm (measured 8.73 mm)\n', 1e3*mean(out.y(end-1e4:end)));

%% 2) closed loop with friction vs the rig
rig = load('rig_15_5_run1.mat').data;
xr = rig.getElement('X [m]').Values;
opts = struct('sigX', 34e-6, 'push', false);   % 34 um: closed-loop noise on the rig
figure; hold on;
iRig = xr.Time > 2 & xr.Time < 20;
plot(xr.Time(iRig) - 2, 1e3*xr.Data(iRig), 'k', 'DisplayName', 'rig');
for ratio = [1.0 1.5]
  plant.Fs = ratio*Fc;
  out = simulate_loop(plant, ctrl, [15 5 15], opts);
  plot(out.t, 1e3*out.x, 'DisplayName', sprintf('sim, Fc %.0f N, Fs = %.1f Fc', Fc, ratio));
  fprintf('Fs = %.1f Fc: %s\n', ratio, huntStats(out.t, out.x, [0 6 12 18]));
end
fprintf('rig          : %s\n', huntStats(xr.Time - 2, xr.Data, [0 6 12 18]));
xlabel('t [s] (rig shifted by 2 s)'); ylabel('x - x_0 [mm]'); grid on; legend('Location', 'best');
title('Closed loop with stick-slip friction vs rig');

function s = huntStats(t, x, edges)
% wander (std) over the last 3 s of each hold, and its dominant frequency
s = '';
for j = 1:numel(edges) - 1
  i = t > edges(j + 1) - 3 & t < edges(j + 1);
  xx = x(i) - mean(x(i));
  F = abs(fft(xx)); f = (0:numel(xx) - 1)'/(numel(xx)*mean(diff(t)));
  band = f > 0.3 & f < 20;
  fb = f(band); [~, k] = max(F(band));
  s = [s sprintf('hold %d: std %.2f mm @ %.1f Hz  ', j, 1e3*std(xx), fb(k))]; %#ok<AGROW>
end
end
