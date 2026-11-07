%% Model workspace of Project_Controller.slx (Data source: MATLAB Code)
% The whole design chain, so the model runs on its own: physical parameters -> state-space model
% -> LQR with integral action -> Kalman filter -> discretization. Needs Control System Toolbox.
% Same computation as plant_model.m + controller_design.m (gain set v3a) + controller_params.m.
% build_controller_model.m copies this file into the model and checks it against those files.

%% Test case (same controller for both, no retuning)
rHigh = 0.015;   % [m] 0.015 (15 -> 5 mm) or 0.020 (20 -> 5 mm)
rLow  = 0.005;   % [m]
tHold = 12;      % [s] rLow, rHigh, rLow for tHold s each (stop time = 3*tHold = 36 s)

%% Physical parameters (project description, Table 1)
R    = 0.55;      % motor resistance [Ohm]
L    = 0.8e-3;    % motor inductance [H]
ki   = 0.036;     % torque constant [Nm/A]
kb   = 0.036;     % back-emf constant [V/(rad/s)]
lead = 0.01;      % ball screw lead [m/rev]
eta  = 1;         % ball screw efficiency (prescribed; real value < 1, robustness checked)
ma   = 0.3;       % actuator moving mass [kg]
ml   = 0.51;      % payload mass [kg]

%% Identified parameters (Section 3 of the report)
ks   = 131.66;    % spring [N/m], static stretch test
bs   = 0.0048;    % damper [Ns/m], free decay, logarithmic decrement
kv   = 0.99;      % input gain relative to Table 1, closed-loop frequency response
tauM = 0.018;     % actuator time constant [s], frequency response (Table 1 gives 31 ms)
tauS = 0.0106;    % sensor lag [s], Balluff -3 dB at 15 Hz

%% State-space model, deviations from the equilibrium point (plant_model.m)
% states [i y ydot x xdot xs]: current, actuator pos/vel, payload pos/vel, sensor state
N  = 2*pi/lead;             % screw ratio, omega = N*ydot [rad/m]
Kf = eta*N*ki;              % actuator force per ampere [N/A]
Kb = kb*N;                  % back emf per actuator speed [V/(m/s)]
Me = tauM*Kf*Kb/R;          % effective moving mass that gives tauM = Me*R/(Kf*Kb) [kg]
A = [ -R/L     0       -Kb/L     0       0        0
         0     0         1       0       0        0
     Kf/Me -ks/Me    -bs/Me   ks/Me   bs/Me       0
         0     0         0       0       1        0
         0  ks/ml     bs/ml  -ks/ml  -bs/ml       0
         0     0         0   1/tauS      0  -1/tauS ];
B = [kv/L; 0; 0; 0; 0; 0];
C = [0 0 0 0 0 1];          % only the (lagged) payload position is measured
n = size(A, 1);

%% LQR with integral action (L3d, L3g), Bryson's rule q_ii = 1/x_max^2, r = 1/u_max^2
% max: i 5 A, y 25 mm (stroke), ydot 0.15 m/s, x 8 mm, xdot 20 mm/s, xs not weighted,
% integral 1 mm*s, voltage 5 V
Ai = [A zeros(n, 1); -C 0];
Bi = [B; 0];
Q  = diag(1 ./ [5 0.025 0.15 0.008 0.02 1e3 0.001].^2);
Ru = 1/5^2;
Kaug = lqr(Ai, Bi, Q, Ru);
K  = Kaug(1:n);             % u = -K*xhat + Ke*xN
Ke = -Kaug(n + 1);

%% Kalman filter (LQE, L3h): process noise as voltage (3 V) and payload force (1 N push)
G   = [B, [0; 0; 0; 0; 1/ml; 0]];
sigX = 22e-6;               % measured sensor noise std [m]
[~, Lobs] = kalman(ss(A, [B G], C, 0), diag([3^2, 1^2]), sigX^2);

%% Discretization at the Speedgoat rate. Observer inputs [u; x]
Ts = 1e-4;                  % [s]
obsD = c2d(ss(A - Lobs*C, [B Lobs], eye(n), 0), Ts);
Ao = obsD.A;  Bo = obsD.B;

%% Holding voltage (equilibrium input) and voltage limit
vMax   = 5;                 % interface limit [V]
vBias  = 0.6;               % measured holding voltage [V]
uLim   = [-vMax, vMax];     % limit on u + vBias [V]

%% Reference prefilter 1/(tauPre*s + 1)^2, outside the loop
tauPre = 0.3;               % [s]
preD = ss(c2d(tf(1, [tauPre^2 2*tauPre 1]), Ts));

%% Start-up from the measured rest position x(0) (it changes between sessions, 1.57-1.85 mm)
x0map  = [0; 1; 0; 1; 0; 1];                     % xhat0 = x0map*x(0): positions = x(0), rest
preMap = (eye(size(preD.A)) - preD.A) \ preD.B;   % prefilter state in steady state at x(0)

%% Chirp excitation (frequency-response identification) and dither: both off
aExc = 0;  tExc = 5;  tExcDur = 60;  fExc1 = 0.3;  fExc2 = 20;
aDither = 0;  fDither = 100;
