% Report figures from the final rig runs
fs = {'rig_final_15_5.mat', 'rig_final_20_5.mat', 'rig_final_push.mat'};
fig = figure('Position', [0 0 1200 900], 'Theme', 'light');
for i = 1:3
  d = load(fs{i}).data; X = d.get('X [m]').Values; t = X.Time; x = 1e3*X.Data;
  rf = x + 1e3*d.get('error').Values.Data; U = d.get('U total').Values.Data;
  rHigh = 15 + 5*(i == 2); rs = 5 + (rHigh - 5)*(mod(t - 2, 12) < 6 & t >= 2);
  subplot(3, 2, 2*i - 1); plot(t, rs, 'k:', t, rf, 'k-', t, x, 'b'); grid on; ylabel('x - x_0 [mm]');
  title(sprintf('%s', strrep(strrep(fs{i}, '.mat', ''), '_', '\_'))); if i == 1, legend('reference step', 'prefiltered reference', 'X measured', 'Location', 'south'); end
  subplot(3, 2, 2*i); plot(t, U, 'Color', [0.85 0.4 0.1]); grid on; ylim([-5.5 5.5]); ylabel('U [V]');
  if i == 3, subplot(3, 2, 5); xlabel('t [s]'); subplot(3, 2, 6); xlabel('t [s]'); end
  if i == 3
    for w = [3.5 5.8; 10.5 12.8]'
      k = t >= w(1) & t < w(2); fprintf('push window %.1f-%.1f s: X %.1f..%.1f mm (ref %.0f)\n', w, min(x(k)), max(x(k)), median(rs(k)));
    end
    [~, j] = max(x); fprintf('max X %.1f mm at %.2f s; ', x(j), t(j)); [~, j] = min(x(t > 3)); tt = t(t > 3); fprintf('min X after 3 s %.1f mm at %.2f s\n', min(x(t > 3)), tt(j));
  end
end
exportgraphics(fig, fullfile(fileparts(mfilename('fullpath')), '..', '..', 'figures', 'final_rig_runs.png'), 'Resolution', 150);
