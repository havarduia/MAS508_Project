function plant = rig_plant(eta, tauM)
% RIG_PLANT  True-plant settings for simulate_loop that reproduce rig runs A, B, C and v2
% (hold wander 1.25 Hz, U chatter ~6 Hz, run C limit cycle; sweeps in the 2026-11-01 session).
%   - actuator gain 1.5x the model (video FRFs showed 1.5-2x at 5-11 Hz)
%   - input bias dv = -0.5 V: holding needs about 0.6 V at the driver in every rig run,
%     the driver map says 0.104 V (gUp*(0.6 - 0.104) = 0.5)
%   - driver stuck band twice as wide as measured with 0.4 s steps
%   - sensor: 14 ms hold + 3.5 ms lag; tauM 18 ms
if nargin < 1, eta = 1; end
if nargin < 2, tauM = 0.018; end
[plant.sys, plant.p] = plant_model(eta, 1.5*0.66, tauM);
plant.dv = -0.5; plant.Fc = 0; plant.Fs = 0;
plant.Tsens = 0.014; plant.tauSens = 0.0035;
plant.drv = driver_map(); plant.drv.uLo = 2*plant.drv.uLo; plant.drv.uHi = 2*plant.drv.uHi;
end
