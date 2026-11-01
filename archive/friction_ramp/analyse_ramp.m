function r = analyse_ramp(t, x, v)
% ANALYSE_RAMP  Static and Coulomb friction from the Friction_ramp.slx run.
%   r = analyse_ramp(t, x, v)  - time [s], payload X [m], total voltage [V]
%   rig: ds = load('rig_ramp_run1.mat').data; X = ds.getElement('X [m]').Values;
%        U = ds.getElement('U total').Values;
%        analyse_ramp(X.Time, squeeze(X.Data), squeeze(U.Data))
%
% Quasi-static: the motor current is (v - vG - Ke*ydot)/R, so its force Kf*i
% balances friction. vG is the voltage that balances gravity.
%   breakaway up/down:  Kf*(vUp - vG)/R = Fs,  Kf*(vG - vDown)/R = Fs
%   sliding:            Kf*(v - vG - Ke*ydot)/R = +-Fc
% Payload follows the actuator through the spring, so ydot = slope of x while sliding.
[~, p] = plant_model(1.0, 1.0);    % friction modelled explicitly, no lumped gain
fs = 1/median(diff(t));
[b, a] = butter(2, 0.5/(fs/2));
xs = filtfilt(b, a, x);              % removes the undamped 2.56 Hz ringing
tP = ramp_profile();
moveThr = 0.5e-3;                    % [m] counts as moved

[r.vUp, iUp]   = breakaway(t, xs, v, [tP(2) tP(3)], +1, moveThr);
[r.vDown, iDn] = breakaway(t, xs, v, [tP(5) tP(6)], -1, moveThr);
r.vG = (r.vUp + r.vDown)/2;
r.Fs = p.Kf*(r.vUp - r.vDown)/(2*p.R);

% sliding: 0.8 s after breakaway (up: stop before the cutoff)
iCut = find(t > t(iUp) & x > 0.9*ramp_cut(), 1); if isempty(iCut), iCut = numel(t); end
r.FcUp   = slideFc(t, x, v, iUp, min(t(iUp) + 0.8, t(iCut)), r.vG, p, +1);
r.FcDown = slideFc(t, x, v, iDn, t(iDn) + 0.8, r.vG, p, -1);
r.Fc = (r.FcUp + r.FcDown)/2;
fprintf('breakaway: up %.2f V, down %.2f V -> gravity balance %.2f V, Fs = %.1f N\n', r.vUp, r.vDown, r.vG, r.Fs);
fprintf('sliding:   Fc = %.1f N (up %.1f, down %.1f)\n', r.Fc, r.FcUp, r.FcDown);

if nargout == 0
  figure('Name', 'Friction ramp');
  subplot(2, 1, 1); plot(t, 1e3*x, t, 1e3*xs); hold on;
  plot(t([iUp iDn]), 1e3*xs([iUp iDn]), 'ro'); ylabel('X [mm]'); grid on; legend('X', 'X low-pass 0.5 Hz', 'breakaway');
  title(sprintf('F_s = %.1f N, F_c = %.1f N, gravity balance %.2f V', r.Fs, r.Fc, r.vG));
  subplot(2, 1, 2); plot(t, v); ylabel('U total [V]'); xlabel('t [s]'); grid on;
  clear r
end
end

function c = ramp_cut()
[~, ~, c] = ramp_profile();
end

function [vB, iB] = breakaway(t, xs, v, win, dir, thr)
i0 = find(t >= win(1), 1);
x0 = xs(i0);
iB = find(t > win(1) & t < win(2) & dir*(xs - x0) > thr, 1);
assert(~isempty(iB), 'no breakaway found between %g and %g s', win);
vB = v(iB);
end

function Fc = slideFc(t, x, v, i1, tEnd, vG, p, dir)
i = t >= t(i1) & t <= tEnd;
c = polyfit(t(i), x(i), 1);          % sliding speed [m/s]
Fc = dir*p.Kf*(mean(v(i)) - vG - p.Ke*c(1))/p.R;
end
