%% Report figures (run after setup_project). Each section writes one PNG to figures/.
figDir = fullfile(fileparts(mfilename('fullpath')), '..', '..', 'figures');
if ~isfolder(figDir), mkdir(figDir); end
save_fig = @(fig, name) saveBoth(fig, fullfile(figDir, name));   % vector EPS for the report + PNG preview
newfig = @(w, h) figure('Position', [0 0 w h], 'Theme', 'light');
g = load('controller_gains_v3a.mat');
% Plot style of the course scripts (mas508_cw34.m, mas508_lab2_exercise1.m): thick lines, Times 14,
% 'Time [s]'-style labels. As in the lectures (L2d), output above and voltage below on a shared time axis,
% Bode plots in dB / deg against log(omega); the LaTeX caption carries the description, not a plot title.
sty = {'DefaultLineLineWidth', 1.5; 'DefaultAxesFontSize', 14; 'DefaultAxesFontName', 'Times'; 'DefaultTextFontName', 'Times'; 'DefaultLegendFontSize', 12};
old = cellfun(@(n) get(groot, n), sty(:, 1), 'UniformOutput', false);
for j = 1:size(sty, 1), set(groot, sty{j, 1}, sty{j, 2}); end

%% 1. Final rig runs: 15->5, 20->5, push (final_rig_runs.png)
% legend in its own tile above the plots so it never covers data
fs = {'rig_final_15_5_24s.mat', 'rig_final_20_5_24s.mat', 'rig_final_15_5_push_24s.mat'};   % 2026-11-05: 12 s holds
names = {'15 \rightarrow 5 mm', '20 \rightarrow 5 mm', '15 \rightarrow 5 mm with pushes'};
fig = newfig(1200, 900); tl = tiledlayout(3, 2, 'TileSpacing', 'compact');
for i = 1:3
  [t, x, rf, U] = rig(fs{i});
  nexttile; plot(t, rf, 'k--', t, x, 'b'); grid on; xlim(t([1 end])); ylabel('Position [mm]'); title(names{i});
  if i == 1, lg = legend('Reference (prefiltered)', 'Measured x', 'Orientation', 'horizontal'); lg.Layout.Tile = 'north'; end
  nexttile; plot(t, U, 'r'); grid on; xlim(t([1 end])); ylim([-5.5 5.5]); ylabel('Voltage [V]'); title('Control input v(t)');
end
xlabel(tl, 'Time [s]', 'FontName', 'Times', 'FontSize', 14);
save_fig(fig, 'final_rig_runs.png');

%% 2. Bode plot: sinusoidal-input run 4 (rig_chirp_run4) against the model with tauM 18 ms and 31 ms (bode_chirp.png)
[f, Gm] = identify_frf(load('rig_chirp_run4.mat').data);
k = f >= 3 & f <= 20; f = f(k); Gm = Gm(k);   % below 3 Hz the loop rejects the sine excitation
G18 = squeeze(freqresp(plant_model(1, 0.99, 0.018, 0.0106), 2*pi*f));
G31 = squeeze(freqresp(plant_model(1, 0.99, 0.0309, 0.0106), 2*pi*f));
ph = @(G) rad2deg(unwrap(angle(G)));
b = f >= 5 & f <= 12; phm = ph(Gm) - 360*round(median(ph(Gm(b)) - ph(G18(b)))/360);   % same 360 deg branch as the model
w = 2*pi*f; fig = newfig(900, 650);
subplot(2, 1, 1); semilogx(w, 20*log10(abs(Gm)), 'k.', w, 20*log10(abs(G18)), 'b-', w, 20*log10(abs(G31)), 'r--'); grid on;
ylabel('Magnitude [dB]'); title('Bode Diagram'); xlim(w([1 end]));
legend('Measured (sinusoidal input)', 'Model, \tau_m = 18 ms', 'Model, \tau_m = 31 ms (Table 1)', 'Location', 'southwest');
subplot(2, 1, 2); semilogx(w, phm, 'k.', w, ph(G18), 'b-', w, ph(G31), 'r--'); grid on; xlim(w([1 end]));
ylabel('Phase [deg]'); xlabel('Frequency [rad/s]');
save_fig(fig, 'bode_chirp.png');

%% 3. Simulation of the final controller on the identified model, same pattern as the rig runs (sim_final.png)
% 5 -> rHigh -> 5 mm, 12 s holds, 1 N push during the high hold; the gain / tauM / eta / delay robustness
% is in the margin table, so only the identified model is shown
ctrl = g; tau = 0.3;
[b, a] = tfdata(c2d(tf(1, [tau^2 2*tau 1]), g.Ts), 'v'); ctrl.pre = struct('b', b, 'a', a, 'N', 0);
fig = newfig(1200, 650); tl = tiledlayout(2, 2, 'TileSpacing', 'compact', 'TileIndexing', 'columnmajor');
for c = 1:2
  refs = [5 15 5] + [0 5 0]*(c == 2);
  pl = simPlant(0.51);
  rng(1); o = simulate_loop(pl, ctrl, refs, struct('sigX', 22e-6, 'push', true, 'tHold', 12, 'tPush', [17.5 18.5]));
  nexttile; plot(o.t, 1e3*o.r, 'k--', o.t, 1e3*o.x, 'b'); grid on; xlim(o.t([1 end])); ylabel('Position [mm]');
  xline(17.5, ':'); xline(18.5, ':'); title(sprintf('%d \\rightarrow 5 mm, 1 N push at 17.5-18.5 s', refs(2)));
  if c == 1, lg = legend('Reference (prefiltered)', 'Simulated x', 'Orientation', 'horizontal'); lg.Layout.Tile = 'north'; end
  nexttile; plot(o.t, o.v, 'r'); grid on; xlim(o.t([1 end])); ylim([-5.5 5.5]); ylabel('Voltage [V]'); title('Control input v(t)');
end
xlabel(tl, 'Time [s]', 'FontName', 'Times', 'FontSize', 14);
save_fig(fig, 'sim_final.png');

%% 4. Controller subsystem as built (simulink_controller.png) and the LQG block diagram (block_diagram.png)
% the generated top level is auto-placed and unreadable, so the LQG structure is drawn by hand
load_system('Project_Controller');
% Simulink print has no EPS export; a 300 dpi PNG of the model diagram is sharp enough
print('-sProject_Controller/Controller', '-dpng', '-r300', fullfile(figDir, 'simulink_controller.png'));
fig = newfig(1000, 360); axes('Position', [0 0 1 1]); axis([0 16 0 5.5]); axis off; hold on;
W = 16; H = 5.5; arr = @(xy) annotation('arrow', xy(:, 1)/W, xy(:, 2)/H, 'HeadLength', 7, 'HeadWidth', 7);
lin = @(xy) plot(xy(:, 1), xy(:, 2), 'k-');
blk = @(x, y, s) [rectangle('Position', [x-0.9 y-0.45 1.8 0.9]), text(x, y, s, 'HorizontalAlignment', 'center', 'FontSize', 14)];
sumc = @(x, y) [rectangle('Position', [x-0.2 y-0.2 0.4 0.4], 'Curvature', 1), text(x, y, '\Sigma', 'HorizontalAlignment', 'center')];
blk(2, 4, {'Prefilter', ['1/(0.3s+1)' char(178)]}); sumc(4, 4); blk(5.8, 4, {'Integrator', 'T_s/(z-1)'}); rectangle('Position', [7.7 3.55 1.2 0.9]); text(8.3, 4, 'K_e', 'HorizontalAlignment', 'center', 'FontSize', 14);
sumc(9.6, 4); blk(11.4, 4, {'+ v_{bias}', 'sat. \pm5 V'}); blk(13.5, 4, 'Plant');
blk(11.4, 1.5, {'Kalman', 'filter'}); blk(7.9, 1.5, 'K');
arr([0.3 4; 1.1 4]); arr([2.9 4; 3.8 4]); arr([4.2 4; 4.9 4]); arr([6.7 4; 7.7 4]); arr([8.9 4; 9.4 4]);
arr([9.8 4; 10.5 4]); arr([12.3 4; 12.6 4]); arr([14.4 4; 15.8 4]);
lin([15 4; 15 0.4; 4 0.4]); arr([4 0.4; 4 3.8]); arr([15 1.5; 12.3 1.5]);        % X to the error and the observer
lin([12.45 4; 12.45 2.6; 11.4 2.6]); arr([11.4 2.6; 11.4 1.95]);                          % applied voltage (minus bias) to the observer
arr([10.5 1.5; 8.8 1.5]); lin([7.0 1.5; 6.3 1.5; 6.3 2.9; 9.6 2.9]); arr([9.6 2.9; 9.6 3.8]);   % xhat -> K -> u
lbl = {0.4 4.25 'r'; 3.2 4.25 'r_f'; 4.35 4.25 'e'; 3.75 3.55 '-'; 7.05 4.25 'x_N'; 9.05 4.25 '+'; 9.8 3.45 '-';
  10.0 4.25 'u'; 12.35 4.25 'v'; 15.3 4.25 'x'; 12.6 2.75 'v - v_{bias}'};
text([lbl{:, 1}], [lbl{:, 2}], lbl(:, 3), 'FontSize', 14, 'FontAngle', 'italic');
text(9.5, 1.75, '$\hat{x}$', 'Interpreter', 'latex', 'FontSize', 15);
text(5.8, 4.75, 'Anti-windup: frozen while saturated', 'HorizontalAlignment', 'center', 'FontSize', 12);
save_fig(fig, 'block_diagram.png');
close_system('Project_Controller', 0);

%% 5. Before/after on the rig, 15 -> 5 mm, on a common time axis (before_after.png)
% The two runs used different hold times (6 s / 12 s), so each event is cut out and plotted against the
% time since it: start-up, up-step and down-step. Same gains in both; the 'before' run did not log r,
% so its step command is redrawn from the known pattern (refStep).
fs = {'rig_v3a_15_5.mat', 'rig_final_15_5_24s.mat'};
tEv = [0 2 8; 0 12 24];                  % start, up-step, down-step [s] in each run
win = [0 2; -1 5.5; -1 5.5];             % window around each event [s]
evName = {'Start-up', 'Up-step 5 \rightarrow 15 mm', 'Down-step 15 \rightarrow 5 mm'};
cB = [0.85 0.33 0.10]; cA = [0 0.2 0.8];   % before / after
R = cell(1, 2);
for i = 1:2, [R{i}.t, R{i}.x, R{i}.rf, R{i}.U] = rig(fs{i}); end
fig = newfig(1200, 600); tl = tiledlayout(2, 3, 'TileSpacing', 'compact', 'TileIndexing', 'columnmajor');
for e = 1:3
  kB = R{1}.t >= tEv(1, e) + win(e, 1) & R{1}.t <= tEv(1, e) + win(e, 2);
  kA = R{2}.t >= tEv(2, e) + win(e, 1) & R{2}.t <= tEv(2, e) + win(e, 2);
  tB = R{1}.t(kB) - tEv(1, e); tA = R{2}.t(kA) - tEv(2, e);
  nexttile; hold on;
  plot(tB, refStep(R{1}.t(kB), 15), 'k--');
  plot(tA, R{2}.rf(kA), 'k:');
  plot(tB, R{1}.x(kB), 'Color', cB); plot(tA, R{2}.x(kA), 'Color', cA);
  grid on; box on; xlim(win(e, :)); ylim([-1 20]); title(evName{e});
  if e == 1
    ylabel('Position [mm]');
    lg = legend('Step command', 'Prefiltered reference (after)', 'Before: step reference', ...
      'After: prefilter + start at rest', 'Orientation', 'horizontal'); lg.Layout.Tile = 'north';
  end
  nexttile; hold on; plot(tB, R{1}.U(kB), 'Color', cB); plot(tA, R{2}.U(kA), 'Color', cA);
  grid on; box on; xlim(win(e, :)); ylim([-5.5 5.5]); if e == 1, ylabel('Voltage [V]'); end
end
xlabel(tl, 'Time since the event [s]', 'FontName', 'Times', 'FontSize', 14);
save_fig(fig, 'before_after.png');

%% 8. Motor-driver characteristic: actuator speed vs voltage, open-loop steps (driver_map.png)
addpath(fullfile(fileparts(mfilename('fullpath')), '..', '..', 'archive', 'driver_test'));   % analyse_driver
T = [];
for f = {'rig_driver_run1.mat', 'rig_driver_run2.mat'}
  ds = load(f{1}).data; gv = @(n) ds.getElement(n).Values; X = gv('X [m]');
  T = [T; analyse_driver(X.Time, squeeze(X.Data), squeeze(gv('step level').Data), squeeze(gv('step active').Data))]; %#ok<AGROW>
end
d = driver_map(); uu = [-1.3 2.1];
fig = newfig(800, 500); hold on;
patch([d.uLo d.uHi d.uHi d.uLo], [-50 -50 65 65], [0.85 0.85 0.85], 'EdgeColor', 'none');
plot(T.U_V, T.speed_mm_s, 'bo', 'MarkerFaceColor', 'b');
plot([d.u0Up uu(2) NaN uu(1) d.u0Dn], [0 29.7*(uu(2) - d.u0Up) NaN 20.1*(uu(1) - d.u0Dn) 0], 'k-');
grid on; box on; ylim([-50 65]); xlabel('Voltage [V]'); ylabel('Actuator velocity [mm/s]');
legend('No motion (friction)', 'Measured', 'Line fit', 'Location', 'northwest');
save_fig(fig, 'driver_map.png');

%% 9. Impulse response of the payload, damping from the logarithmic decrement (bs_ringdown.png)
x1 = load('ringdown_runs.mat').x1;
identify_bs(x1.Time, squeeze(x1.Data), 0.51);
fig = gcf; fig.Position = [0 0 900 700]; fig.Theme = 'light';
save_fig(fig, 'bs_ringdown.png');

%% 10. Open-loop pulse response against the model (validate_last_run.png)
% pulse_run3.mat (2026-11-06): 0 V rest (no jitter before the pulse), 1 V + 0.3 V holding step at t = 2 s, 0.3 V hold after.
% Without the hold the payload weight back-drives the actuator to the start (pulse_run2.mat); last_run.mat held 0.3 V throughout and jittered at rest.
d = load('pulse_run3.mat').data;
u = d.getElement(1).Values; X = d.get('X [m]').Values;   % two signals are named 'u', both signed here
validate_step(u.Time, u.Data - 0.3*(u.Time >= 2), X.Data);   % model sees the 1 V pulse only
fig = gcf; fig.Position = [0 0 1000 700]; fig.Theme = 'light';
save_fig(fig, 'validate_last_run.png');

%% 11. Pulse runs against the linear and the friction model (friction_validation.png)
% Same 1 V, 0.3 s pulse; only the holding voltage after it differs. friction_plant: Table 1 + measured
% driver map (driver test) + breakaway time from the end stop fitted on run 3 (validate_friction prints the table).
[~, sv] = validate_friction();
s = sv(2);   % run 4 (hold 0.19 V): a validation run, not used for the fit; the table covers all runs
fig = newfig(1000, 450);
plot(s.t, s.x, 'b', s.t, s.xLin, 'k--'); hold on; plot(s.t, s.xFric, 'Color', [0.85 0.33 0.1]);
grid on; xlim([0 10]); ylim([-1 18]); ylabel('Position [mm]'); xlabel('Time [s]');
legend('Measured', 'Linear model', 'Friction model', 'Location', 'northoutside', 'Orientation', 'horizontal');
save_fig(fig, 'friction_validation.png');

for j = 1:size(sty, 1), set(groot, sty{j, 1}, old{j}); end

%% Local functions
function saveBoth(fig, png)
exportgraphics(fig, strrep(png, '.png', '.eps'), 'ContentType', 'vector');
exportgraphics(fig, png, 'Resolution', 200);
end

function pl = simPlant(ml)
% identified model (gain 0.99, tauM 18 ms) with the measured holding bias, sensor sampling + lag and driver characteristic
[pl.sys, pl.p] = plant_model(1, 0.99, 0.018, 0, ml);
pl.Fc = 0; pl.Fs = 0; pl.Tsens = 0.014; pl.tauSens = 0.0035; pl.drv = driver_map();
% driver_map gains are relative to a gain-0.66 plant; rescale so this gain-0.99 plant gives the measured mm/s per V
s = 0.66/pl.p.kv; pl.drv.gUp = s*pl.drv.gUp; pl.drv.gDn = s*pl.drv.gDn;
pl.dv = -pl.drv.gUp*(0.6 - pl.drv.u0Up);   % holding takes 0.6 V at the driver, as on the rig
end

function [t, x, rf, U] = rig(file)
% rig run: time, payload x [mm], prefiltered reference [mm] (x + error), total voltage [V]
d = load(file).data; X = d.get('X [m]').Values;
t = X.Time; x = 1e3*X.Data; rf = x + 1e3*d.get('error').Values.Data; U = d.get('U total').Values.Data;
end

function rs = refStep(t, rHigh)
% the reference step pattern: 5 mm for 2 s, then rHigh / 5 mm for 6 s each
rs = 5 + (rHigh - 5)*(mod(t - 2, 12) < 6 & t >= 2);
end
