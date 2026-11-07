%% Observer noise sweep: what the Kalman noise levels in controller_design.m do
% Final LQR gains fixed; varies the process noise (voltage qv [V], payload force qF [N]) and the sensor noise
% sigX one at a time, and prints the slowest observer pole (and its ratio to the dominant controller pole,
% L3e asks >= 2), the LQG margins at the identified plant and the lowest damping over the 10 uncertainty
% cases of controller_design.m. Saves nothing. Final values: qv 3 V, qF 1 N, sigX 22 um (first row).
clearvars; sigX = 22e-6; kv = 0.99; tauM = 0.018; tauS = 0.0106;
[sys, p] = plant_model(1, kv, tauM, tauS); [A, B, C, ~] = ssdata(sys); n = size(A, 1);
Ai = [A zeros(n, 1); -C 0]; Bi = [B; 0];
G = [B, [0; 0; 0; 0; 1/p.ml; 0]];
Q = diag(1 ./ [5 0.025 0.15 0.008 0.02 1e3 0.001].^2); R = 1/5^2;
Kaug = lqr(Ai, Bi, Q, R); K = Kaug(1:n); Ke = -Kaug(n + 1); sig = min(-real(eig(Ai - Bi*Kaug)));
tests = [1 .66 .018 0; 1 .99 .018 0; 1 1.32 .018 0; 1 .99 .012 0; 1 .99 .031 0; .66 .99 .018 0;
         1 .99 .018 .005; 1 1.32 .018 .005; 1 1.32 .012 .005; .66 .66 .031 .005];
cases = [3 1; 0.75 1; 1.5 1; 6 1; 12 1; 3 0.25; 3 0.5; 3 2; 3 4; 3 1; 3 1];
sx = [22 22 22 22 22 22 22 22 22 11 44]*1e-6;
for c = 1:size(cases, 1)
  qv = cases(c, 1); qF = cases(c, 2);
  [~, Lobs] = kalman(ss(A, [B G], C, 0), diag([qv^2, qF^2]), sx(c)^2);
  eo = eig(A - Lobs*C);
  ctl = ss([A - B*K - Lobs*C, B*Ke; zeros(1, n) 0], [Lobs; -1], [-K Ke], 0);
  [gm, pm] = margin(-ctl*sys);
  z = zeros(1, size(tests, 1));
  for t = 1:size(tests, 1)
    P = plant_model(tests(t, 1), tests(t, 2), tests(t, 3), tauS);
    if tests(t, 4) > 0, P = ss(P*pade(tf(1, 1, 'InputDelay', tests(t, 4)), 3)); end
    ev = eig(feedback(P, ctl, +1)); ev = ev(abs(ev) > 1e-6); z(t) = min(-real(ev)./abs(ev));
  end
  fprintf('qv %5.2f V qF %4.2f N sigX %2.0f um: slowest obs pole %6.1f (%.1fx ctrl) | GM %4.1f PM %4.1f | zeta_min %.2f | |L| x-row %.3g\n', ...
    qv, qF, 1e6*sx(c), min(-real(eo)), min(-real(eo))/sig, 20*log10(gm), pm, min(z), Lobs(4));
end
