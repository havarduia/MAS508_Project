%% Parameters for Project_Controller.slx and Controller_test.slx
% Controller_test.slx runs this in its InitFcn. Project_Controller.slx does NOT: build_controller_model.m
% stores these values in its model workspace, so the .slx runs on its own. Rebuild after changing this file.
% Gains come from controller_design.m.
% Gain set = suffix of controller_gains_<gainSet>.mat. Default v3a (controller_design.m).
% Older sets: 'v3b', 'v2', 'v1' (runs A, B, v1, dither), 'soft_v1' (run C).
if ~exist('gainSet', 'var'), gainSet = 'v3a'; end
g = load(['controller_gains_' gainSet '.mat']);
K = g.K; Ke = g.Ke; Ts = g.Ts; vMax = g.vMax;

% Holding voltage = the equilibrium input (L2b/L2c). Identified from every rig run:
% the driver needs about 0.6 V to hold still (the 0.3 V in the gains files was a placeholder).
vBias = 0.6;
uLim = [-vMax, vMax];   % controller voltage limit [lower upper] on u + vBias

% Observer xhat' = (A - L*C)*xhat + B*u + L*x, discretized at the Speedgoat rate.
% Inputs [u; x], u = applied voltage minus the holding bias.
obsD = c2d(ss(g.A - g.Lobs*g.C, [g.B g.Lobs], eye(size(g.A, 1)), 0), Ts);
Ao = obsD.A; Bo = obsD.B;

% Reference: rLow, rHigh, rLow for tHold s each.
% Second test case: Project_Controller.slx: Model Explorer > Model Workspace > edit rHigh = 0.020 in the code
% (a base-workspace rHigh is ignored there). Controller_test.slx: set rHigh in the base workspace. Same gains.
if ~exist('rHigh', 'var'), rHigh = 0.015; end
if ~exist('rLow', 'var'), rLow = 0.005; end   % chirp run: rHigh = rLow = 0.010

% Reference prefilter 1/(tauPre*s + 1)^2 (critically damped, no overshoot of its own): the
% integral controller then follows a smooth reference instead of a step. On the rig the step
% gave 20-32 % overshoot and +-5 V bursts. It sits outside the loop: K, Ke, L and the margins
% are unchanged. tauPre from simulation (2026-11-01): 0.3 s keeps the 10-90 % rise ~1.1 s,
% overshoot ~3 %, no voltage saturation. tauPre = 0 gives the plain step.
if ~exist('tauPre', 'var'), tauPre = 0.3; end
if tauPre > 0
  preD = ss(c2d(tf(1, [tauPre^2 2*tauPre 1]), Ts));
else
  preD = ss(1, 0, 0, 1, Ts);
end

% Start-up at rest: prefilter, observer and integrator start in the equilibrium at the MEASURED
% first x (relative to the equilibrium all positions are equal, velocities and current 0), with
% the integrator holding the voltage that keeps it there. A fixed start (1.6 mm) gave a -5/+5 V
% kick on 2026-11-05, when the payload rested at 1.85 mm (rest varies 1.57-1.85 mm).
x0map = [0; 1; 0; 1; 0; 1];                     % observer start xhat0 = x0map*x(0)
preMap = (eye(size(preD.A)) - preD.A) \ preD.B;   % prefilter start = preMap*x(0)
if ~exist('xPlant0', 'var'), xPlant0 = 0.0016; end   % Controller_test plant rest position [m]
if ~exist('tHold', 'var'), tHold = 12; end          % [s] each of rLow, rHigh, rLow

% Nominal plant for Controller_test.slx (input: voltage minus bias, output: x)
plantD = c2d(plant_model(), Ts);

% Chirp excitation added to the control voltage, for frequency-response
% identification (identify_frf.m). Off unless aExc > 0 is set in the workspace.
% Linear sweep fExc1 -> fExc2 Hz over tExcDur s, starting at tExc s.
if ~exist('aExc', 'var'), aExc = 0; end

% Dither: a constant 100 Hz sine on the voltage keeps the actuator from sticking in the
% driver's stuck band, which otherwise makes the integrator hunt (+-1 mm at 1.25-1.75 Hz
% on the rig, reproduced with rig_plant.m). Too fast for the payload (2.5 Hz mode) to follow.
if ~exist('aDither', 'var'), aDither = 0; end   % off: no effect on the rig (rig_dither_run2)
fDither = 100;
tExc = 5; tExcDur = 60; fExc1 = 0.3; fExc2 = 20;
