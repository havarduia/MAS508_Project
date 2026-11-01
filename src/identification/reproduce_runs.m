%% REPRODUCE_RUNS  Does the updated true plant reproduce rig runs A, B and C?
% True plant: tauM = 18 ms (chirp run 4 + video), sensor hold 14 ms + 3.5 ms lag,
% measured driver map. Compares hold statistics: std and dominant frequency of X and U.
%   A: nominal gains, no inverse map (vBias 0.3)
%   B: nominal gains + inverse driver map
%   C: soft gains + inverse driver map
rng(1);
[plant.sys, plant.p] = plant_model(1, 0.66, 0.018);
plant.dv = 0; plant.Fc = 0; plant.Fs = 0;
plant.Tsens = 0.014; plant.tauSens = 0.0035;
plant.drv = driver_map();
opts.sigX = 22e-6; opts.push = false;

runs = {'A', 'controller_gains_v1.mat', false
        'B', 'controller_gains_v1.mat', true
        'C', 'controller_gains_soft_v1.mat', true};
% last 4 s of each hold; rig: 2 s low then 6 s high/low, sim: 6 s per ref from t = 0
rigWin = [4 8; 10 14; 16 20; 22 26];
simWin = [8 12; 14 18; 20 24];
refs = [5 15 5 15];

fprintf('%-4s %-4s %10s %8s %10s %8s\n', 'run', '', 'X std mm', 'X Hz', 'U std V', 'U Hz');
for i = 1:size(runs, 1)
  ctrl = load(runs{i, 2});
  if runs{i, 3}, ctrl.vBias = 0; ctrl.inv = driver_map(); end
  out = simulate_loop(plant, ctrl, refs, opts);

  d = load(['rig_run_' runs{i, 1} '.mat']).data;
  tr = d.get('X [m]').Values.Time;
  xr = d.get('X [m]').Values.Data;
  ur = d.get('U driver').Values.Data;

  [sx, fx] = holdStats(tr, 1e3*xr, rigWin); [su, fu] = holdStats(tr, ur, rigWin);
  fprintf('%-4s %-4s %10.3f %8.2f %10.3f %8.2f\n', runs{i, 1}, 'rig', sx, fx, su, fu);
  [sx, fx] = holdStats(out.t, 1e3*out.xm, simWin); [su, fu] = holdStats(out.t, out.v, simWin);
  fprintf('%-4s %-4s %10.3f %8.2f %10.3f %8.2f\n', '', 'sim', sx, fx, su, fu);
end

function [s, fPk] = holdStats(t, z, win)
% mean std over the hold windows, and the peak of the averaged spectrum in 0.5-20 Hz
Ts = t(2) - t(1); s = 0; P = 0;
n = round((win(1, 2) - win(1, 1))/Ts);
for w = 1:size(win, 1)
  k = find(t >= win(w, 1), 1) + (0:n - 1);
  zw = detrend(z(k));
  s = s + std(zw)/size(win, 1);
  P = P + abs(fft(zw .* hann(n))).^2;
end
f = (0:n - 1)'/(n*Ts);
band = f >= 0.5 & f <= 20;
[~, j] = max(P .* band);
fPk = f(j);
end
