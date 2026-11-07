function [sys, p] = plant_model(eta, kv, tauM, tauS, ml)
% PLANT_MODEL  BLDC motor + ball screw + spring/damper + payload
%   [sys, p] = plant_model(eta, kv, tauM, tauS, ml)
%     eta - ball screw efficiency (default 1.0, as the project description says)
%     kv  - effective input voltage gain (default 0.66, from validate_step on
%           last_run.mat: the payload travelled 0.66 x the modelled distance).
%           Lumps friction and driver losses: part of the voltage only keeps
%           the stage sliding. eta cannot explain it, since the pulse travel
%           is set by the back-emf speed limit ydot = v/Ke, not by eta.
%     tauM - effective actuator time constant Me*R/(Kf*Ke) [s] (default [] = from
%           the datasheet values, 31 ms). The rig responds about 2x faster at
%           6-12 Hz (run C limit cycle, chirp-run video), about 10-20 ms: the
%           in-house driver is faster than a plain voltage drive. Sets Me.
%     tauS - position sensor lag [s] (default 0 = ideal sensor). Adds state x6 =
%           measured position, x6' = (x - x6)/tauS, and the output becomes x6.
%           Balluff BAW003K: -3 dB at 15 Hz (10.6 ms), matching our own staircase
%           data (3.5 ms lag + 7 ms average delay of the ~14 ms update).
%     ml   - payload mass [kg] (default 0.51, Table 1); for mass robustness checks
%     sys - state space model, p - struct with the parameters
%   plant_model()  with no outputs prints the model checks.
%
% States (deviations from static equilibrium, so gravity drops out, L2b/L2c):
%   x1 = i     armature current        [A]
%   x2 = y     actuator position       [m]
%   x3 = ydot  actuator velocity       [m/s]
%   x4 = x     payload position        [m]
%   x5 = xdot  payload velocity        [m/s]
% Input: v [V] (on top of the 0.3 V holding bias).  Output: payload position x.

if nargin < 1, eta = 1.0; end
if nargin < 2, kv = 0.66; end
if nargin < 3, tauM = []; end
if nargin < 4, tauS = 0; end
if nargin < 5, ml = 0.51; end

%% Parameters (Table 1)
p.ma   = 0.3;        % actuator moving mass [kg]
p.R    = 0.55;       % [Ohm]
p.L    = 0.8e-3;     % [H]
p.ki   = 0.036;      % [Nm/A]
p.kb   = 0.036;      % [V/(rad/s)]
p.Jm   = 72e-6;      % [kg m^2]
p.lead = 0.01;       % ball screw lead [m/rev]
p.eta  = eta;
p.kv   = kv;
p.ml   = ml;         % payload mass [kg]
p.g    = 9.81;
p.x0   = 0.00526;    % payload rest position, actuator at bottom (y = 0) [m]
p.ks   = 131.66;     % [N/m]   free-decay test (identify_bs)
p.bs   = 0.0048;     % [Ns/m]  impulse response, logarithmic decrement, zeta = 0.00030 (identify_bs)

%% Derived quantities
p.N  = 2*pi/p.lead;                 % screw ratio: omega = N*ydot  [rad/m]
p.Kf = p.eta*p.N*p.ki;              % force per amp at the nut     [N/A]
p.Ke = p.kb*p.N;                    % back-emf per actuator speed  [V/(m/s)]
p.Me = p.ma + p.eta*p.Jm*p.N^2;     % actuator mass incl. reflected motor inertia [kg]
if ~isempty(tauM), p.Me = tauM*p.Kf*p.Ke/p.R; end   % effective mass for the measured speed of response
p.tauM = p.Me*p.R/(p.Kf*p.Ke); p.tauS = tauS;

%% State space
R = p.R; L = p.L; Ke = p.Ke; Kf = p.Kf; Me = p.Me; ks = p.ks; bs = p.bs; ml = p.ml;
A = [ -R/L     0        -Ke/L     0       0
         0     0          1       0       0
     Kf/Me -ks/Me    -bs/Me   ks/Me   bs/Me
         0     0          0       0       1
         0  ks/ml     bs/ml  -ks/ml  -bs/ml ];
B = [kv/L; 0; 0; 0; 0];
C = [0 0 0 1 0];
names = {'i','y','ydot','x','xdot'};
if tauS > 0
  A = [A zeros(5, 1); 0 0 0 1/tauS 0 -1/tauS];
  B = [B; 0]; C = [0 0 0 0 0 1]; names{6} = 'xs';
end
sys = ss(A, B, C, 0, 'StateName', names, 'InputName', 'v', 'OutputName', 'x');

if nargout == 0
  fprintf('eta = %.2f, kv = %.2f\n', p.eta, p.kv);
  fprintf('Me = %.2f kg (reflected inertia %.2f kg vs ma %.2f kg)\n', Me, Me - p.ma, p.ma);
  fprintf('Kf = %.2f N/A, holding current = %.3f A, static stretch = %.1f mm\n', ...
    Kf, (p.ma + ml)*p.g/Kf, 1e3*ml*p.g/ks);
  fprintf('Electrical time constant L/R = %.2f ms\n', 1e3*L/R);
  fprintf('Spring-payload natural freq ~ %.2f Hz\n', sqrt(ks/ml)/(2*pi));
  disp('Open-loop poles:'); disp(eig(A));
  fprintf('rank obsv = %d (n = %d); for controllability see ctrb_calc (Hautus)\n', ...
    rank(obsv(A, C)), size(A, 1));
end
end
