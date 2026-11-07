%% Weight sweep: why the final Bryson maxima (controller_design.m) have the values they have
% Varies one LQR weight at a time around the final design (others fixed, same Kalman observer) and prints
% the settling estimate 4/sigma, the gain/phase margins at the identified plant and the lowest closed-loop
% damping over the same 10 uncertainty cases as controller_design.m. Saves nothing.
% Result: x_max and v_max barely matter; xdot_max = 20 mm/s gives the best worst-case damping;
% x_N max = 1 mm s trades settling (1.2 s, inside the 2 s target) against margins.
clearvars; sigX = 22e-6; kv = 0.99; tauM = 0.018; tauS = 0.0106;
[sys, p] = plant_model(1, kv, tauM, tauS); [A, B, C, ~] = ssdata(sys); n = size(A, 1);
Ai = [A zeros(n, 1); -C 0]; Bi = [B; 0];
G = [B, [0; 0; 0; 0; 1/p.ml; 0]];
[~, Lobs] = kalman(ss(A, [B G], C, 0), diag([3^2, 1^2]), sigX^2);
tests = [1 .66 .018 0; 1 .99 .018 0; 1 1.32 .018 0; 1 .99 .012 0; 1 .99 .031 0; .66 .99 .018 0;
         1 .99 .018 .005; 1 1.32 .018 .005; 1 1.32 .012 .005; .66 .66 .031 .005];
base = [0.008 0.02 0.001 5];   % xMax xdMax xNMax uMax
names = {'x_max [mm]', 'xdot_max [mm/s]', 'x_N max [mm s]', 'v_max [V]'};
vals = {[0.002 0.004 0.008 0.016 0.032], [0.005 0.01 0.02 0.04 0.08], [0.00025 0.0005 0.001 0.002 0.004], [1.25 2.5 5 10 20]};
scale = [1e3 1e3 1e3 1];
for w = 1:4
  fprintf('\n%s\n', names{w});
  for val = vals{w}
    b = base; b(w) = val;
    Q = diag(1 ./ [5 0.025 0.15 b(1) b(2) 1e3 b(3)].^2); R = 1/b(4)^2;
    Kaug = lqr(Ai, Bi, Q, R); K = Kaug(1:n); Ke = -Kaug(n + 1);
    ec = eig(Ai - Bi*Kaug); sig = min(-real(ec));
    ctl = ss([A - B*K - Lobs*C, B*Ke; zeros(1, n) 0], [Lobs; -1], [-K Ke], 0);
    [gm, pm] = margin(-ctl*sys);
    z = zeros(1, size(tests, 1));
    for t = 1:size(tests, 1)
      P = plant_model(tests(t, 1), tests(t, 2), tests(t, 3), tauS);
      if tests(t, 4) > 0, P = ss(P*pade(tf(1, 1, 'InputDelay', tests(t, 4)), 3)); end
      ev = eig(feedback(P, ctl, +1)); ev = ev(abs(ev) > 1e-6); z(t) = min(-real(ev)./abs(ev));
    end
    eo = eig(A - Lobs*C);
    fprintf('  %7.2f%s: ts 4/sigma %.2f s | GM %5.1f dB PM %5.1f | zeta_min over cases %5.2f | obs/ctrl %.1f\n', ...
      scale(w)*val, repmat('*', 1, isequal(b, base)), 4/sig, 20*log10(gm), pm, min(z), min(-real(eo))/sig);
  end
end
