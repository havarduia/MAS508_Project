function [f, Gm, Gmodel, coh] = identify_frf(ds)
% IDENTIFY_FRF  Measured frequency response U -> X from a chirp run (L2d, frequency domain)
%   [f, Gm, Gmodel, coh] = identify_frf(ds)
%     ds - Dataset with the logged signals 'excitation', 'U total' and 'X [m]':
%          rig:  ds = load('rig_chirp_run1.mat').data;
%          sim:  out.logsout from Controller_test
%     f - frequency [Hz], Gm - measured U -> X [m/V], Gmodel - plant_model at f,
%     coh - coherence excitation -> X (near 1 = trustworthy point)
%   Without outputs it plots measured vs model.
%
% Closed loop, so U is partly a reaction to sensor noise. Estimating
% U -> X directly would be biased; both are instead measured against the
% injected chirp d, which the noise does not contain: G = (d -> X)/(d -> U).

d = ds.getElement('excitation').Values;
U = ds.getElement('U total').Values;
X = ds.getElement('X [m]').Values;
t = d.Time; fs = 1/median(diff(t));
on = find(squeeze(d.Data) ~= 0);
i = on(1):on(end);                        % the chirp window only
dd = squeeze(d.Data(i)); uu = squeeze(U.Data(i)); xx = squeeze(X.Data(i));
uu = uu - mean(uu); xx = xx - mean(xx);

% One FFT over the whole sweep, then average neighbouring frequency bins.
% (Welch segments do not work for a sweep: each frequency is only excited in
% one segment, the others add only disturbance, and coherence collapses.)
n = numel(dd);
D = fft(dd); Uf = fft(uu); Xf = fft(xx);
fAll = (0:n - 1)'*fs/n;
nb = round(0.25/(fs/n));                  % smooth over 0.25 Hz
sm = @(z) movmean(z, nb);
Sdx = sm(conj(D).*Xf); Sdu = sm(conj(D).*Uf); Sdd = sm(abs(D).^2); Sxx = sm(abs(Xf).^2);
f = logspace(log10(0.3), log10(20), 200)';
k = round(f/(fs/n)) + 1;
Gm  = Sdx(k) ./ Sdu(k);
coh = abs(Sdx(k)).^2 ./ (Sdd(k).*Sxx(k));
f = fAll(k);
Gmodel = squeeze(freqresp(plant_model(), 2*pi*f));

if nargout == 0
  band = f > 0.3 & f < 20;
  figure('Name', 'Frequency response U -> X');
  subplot(3, 1, 1);
  loglog(f(band), 1e3*abs(Gm(band)), '.', f(band), 1e3*abs(Gmodel(band)), '-');
  ylabel('|X/U| [mm/V]'); grid on; legend('measured (chirp)', 'plant\_model', 'Location', 'best');
  title('Frequency response from voltage to payload position');
  subplot(3, 1, 2);
  semilogx(f(band), rad2deg(unwrap(angle(Gm(band)))), '.', f(band), rad2deg(unwrap(angle(Gmodel(band)))), '-');
  ylabel('phase [deg]'); grid on;
  subplot(3, 1, 3);
  semilogx(f(band), coh(band), '.'); ylim([0 1.05]);
  ylabel('coherence'); xlabel('f [Hz]'); grid on;
end
end
