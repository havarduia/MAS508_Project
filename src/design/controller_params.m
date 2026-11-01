%% Parameters for Project_Controller.slx and Controller_test.slx
% Run automatically by the models' InitFcn. Gains come from controller_design.m.
% Gain set = suffix of controller_gains_<gainSet>.mat. Default v3a (controller_design.m).
% Older sets: 'v3b', 'v2', 'v1' (runs A, B, v1, dither), 'soft_v1' (run C).
if ~exist('gainSet', 'var'), gainSet = 'v3a'; end
g = load(['controller_gains_' gainSet '.mat']);
K = g.K; Ke = g.Ke; Ts = g.Ts; vBias = g.vBias; vMax = g.vMax;

% Inverse of the measured motor-driver map (driver_map.m) between the controller
% and the analog outputs, so the controller sees the linear plant it was designed
% for. The map's offsets replace the 0.3 V holding bias. useInv = 0 restores the old setup.
% Default off, as in run A (run B with the map held worse: 0.52 vs 0.39 mm).
% Off (final). Tried on 2026-11-01 against the down-step overshoot (rig_inv_*): no measurable
% change (24-40 % vs 21-34 %). The video shows why: in closed loop the actuator stays stuck
% until about -0.8 V going down, much wider than the stuck band in driver_map.m.
if ~exist('useInv', 'var'), useInv = 0; end
drv = driver_map(); gUp = drv.gUp; u0Up = drv.u0Up; gDn = drv.gDn; u0Dn = drv.u0Dn;
% Holding voltage = the equilibrium input (L2b/L2c). Identified from every rig run:
% the driver needs about 0.6 V to hold still (the 0.3 V in the gains files was a placeholder).
vBias0 = 0.6;
if useInv, vBias = 0; else, vBias = vBias0; end

% Controller voltage limit [lower upper] on u + vBias. With the inverse map on, the
% limit is on the command w, set so the map's output stays inside +-vMax: otherwise
% the interface clips it (the -5 V command became -7 V, clipped to -5 V) while the
% observer and anti-windup assume the full command was applied.
if useInv, uLim = [gDn*(-vMax - u0Dn), gUp*(vMax - u0Up)]; else, uLim = [-vMax, vMax]; end

% Observer xhat' = (A - L*C)*xhat + B*u + L*x, discretized at the Speedgoat rate.
% Inputs [u; x], u = applied voltage minus the holding bias.
obsD = c2d(ss(g.A - g.Lobs*g.C, [g.B g.Lobs], eye(size(g.A, 1)), 0), Ts);
Ao = obsD.A; Bo = obsD.B;

% Reference: rLow for 2 s, then rHigh and rLow for 6 s each, repeating.
% Second test case: set rHigh = 0.020 in the workspace before running. Same gains.
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

% Start-up at rest instead of at zero: the payload rests at X = 1.6 mm in every rig run
% (1.57-1.78 mm). Prefilter, observer and integrator start in the equilibrium at that
% position (relative to the equilibrium all positions are equal, velocities and current 0),
% with the integrator holding the voltage that keeps it there. Before this the observer
% started 1.6 mm off and the first 0.3 s saturated at +-5 V.
xRest = 0.0016;
xPre0 = (eye(size(preD.A)) - preD.A) \ preD.B * xRest;
xhat0 = [0; xRest; 0; xRest; 0; xRest];
wRest = useInv*gUp*(vBias0 - u0Up);    % command whose inverse map gives the holding voltage
xN0 = (K*xhat0 + wRest)/Ke;

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
