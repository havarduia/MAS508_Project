function [bs, ks_dyn, zeta, wn] = identify_bs(t, x, ml)
% IDENTIFY_BS  Damping bs from a free-decay (ring-down) test of the payload.
%   [bs, ks_dyn, zeta, wn] = identify_bs(t, x, ml)
%     t  - time [s], x - payload position [m] (actuator held still, payload
%          pulled down and released), ml - payload mass [kg] (default 0.51)
%   identify_bs()  runs a self-check on synthetic data.
%
% Model: ml*xdd + bs*xd + ks*x = 0  ->  amplitude decays as exp(-sigma*t),
% sigma = bs/(2*ml). Amplitude = (peak - next trough)/2, so the resting
% position is never needed and the log does not have to run until settled.
% sigma comes from a line fit of log(amplitude) vs time over all cycles.
%
% From an SLRT run in the Simulation Data Inspector:
%   ids = Simulink.sdi.getAllRunIDs;  r = Simulink.sdi.getRun(ids(end));
%   s = r.getSignalsByName('Payload position X[m]');
%   identify_bs(s.Values.Time, s.Values.Data, 0.51)

if nargin == 0, selfCheck(); return; end
if nargin < 3, ml = 0.51; end
t = t(:); x = x(:);

% Release = end of the largest excursion (skips a hold-down plateau before letting go)
xc = x - median(x);
[Amax, i0] = max(abs(xc));
while i0 < numel(x) && abs(xc(i0 + 1)) >= 0.98*Amax
  i0 = i0 + 1;
end
t = t(i0:end); x = x(i0:end);

prom = 0.05*Amax;
ip = find(islocalmax(x, 'MinProminence', prom));
% sensor noise can split one crest into twin maxima a few ms apart, so
% enforce half a period between extrema (median spacing is robust to twins)
sep = 0.5*median(diff(t(ip)));
ip = find(islocalmax(x, 'MinProminence', prom, 'MinSeparation', sep, 'SamplePoints', t));
it = find(islocalmin(x, 'MinProminence', prom, 'MinSeparation', sep, 'SamplePoints', t));
% pair each peak with the first trough after it
ip = ip(ip < max([it; 0]));
k = zeros(size(ip));
for j = 1:numel(ip)
  k(j) = it(find(it > ip(j), 1));
end
if numel(ip) < 3
  error('identify_bs:fewPeaks', 'Only %d usable cycles, need >= 3. Longer log or larger release?', numel(ip));
end
Ap = (x(ip) - x(k))/2;
tp = (t(ip) + t(k))/2;

p = polyfit(tp, log(Ap), 1);
sigma = -p(1);
wd = 2*pi*(numel(ip) - 1) / (t(ip(end)) - t(ip(1)));
wn = sqrt(wd^2 + sigma^2);
zeta = sigma / wn;
bs = 2*ml*sigma;
ks_dyn = ml*wn^2;

fprintf('cycles used: %d over %.1f s, amplitude %.2f -> %.2f mm\n', numel(ip), tp(end) - tp(1), 1e3*Ap(1), 1e3*Ap(end));
fprintf('fd = %.3f Hz, zeta = %.5f\n', wd/(2*pi), zeta);
fprintf('bs = %.4f Ns/m, ks (dynamic) = %.2f N/m\n', bs, ks_dyn);

if nargout == 0
  figure;
  subplot(2,1,1);
  plot(t, x*1e3); xlabel('t [s]'); ylabel('x [mm]'); grid on; title('Free decay');
  subplot(2,1,2);
  semilogy(tp, Ap*1e3, 'o'); hold on;
  semilogy(tp, 1e3*exp(polyval(p, tp)), '--');
  xlabel('t [s]'); ylabel('amplitude [mm]'); grid on;
  % straight line on this plot = viscous damping; curving down = friction dominates
  legend('measured', sprintf('fit, \\sigma = %.4f 1/s', sigma));
  title(sprintf('b_s = %.4f Ns/m, \\zeta = %.5f', bs, zeta));
end
end

function selfCheck()
ml = 0.51; ks = 131.66; bsTrue = 0.023;   % ~3 min to settle
sys = ss([0 1; -ks/ml -bsTrue/ml], [0; 0], [1 0], 0);
tr = (0:1e-3:45)';
xr = initial(sys, [-5e-3; 0], tr);
% 2 s held down before release, log stops long before settling, offset + noise
x = [-5e-3*ones(2000,1); xr] + 0.020 + 10e-6*randn(numel(xr) + 2000, 1);
% twin crests like the real sensor: copy a crest 4 ms later on every 5th cycle
ipk = find(islocalmax(x, 'MinProminence', 1e-4));
for j = ipk(5:5:end)'
  x(j+4) = x(j) + 1e-6;
end
t = (0:numel(x) - 1)' * 1e-3;
[bs, ksd] = identify_bs(t, x, ml);
assert(abs(bs - bsTrue)/bsTrue < 0.05, 'bs off: %.4f vs %.4f', bs, bsTrue);
assert(abs(ksd - ks)/ks < 0.02, 'ks off: %.2f vs %.2f', ksd, ks);
disp('identify_bs self-check passed');
end
