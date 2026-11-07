function plant = friction_plant()
% FRICTION_PLANT  Linear plant + measured friction/driver behaviour, for simulate_loop.
% Everything comes from the open-loop driver test (rig_driver_run1/2, driver_map.m), except
% tBreak, fitted on pulse_run3; pulse_run2/4 and last_run validate it (validate_friction.m).
%   - stuck from rest while U is inside the measured band, sliding speed on the measured
%     up/down lines (kv 0.66 x gUp/gDn reproduces the measured mm/s per V)
%   - restick: no drive once U is back inside the band (rig: no creep at 0.3 V after a pulse,
%     although the up line would give 6 mm/s)
%   - coast at U = 0: the interface sends magnitude 0, the motor carries no current and the
%     weight back-drives the screw (pulse_run2 falls back to the start)
%   - bottom end stop at the start position; leaving it takes tBreak. The driver test (steps
%     from mid-stroke) shows no such delay; every pulse run (from the stop) starts late
%   - measured sensor update rate and lag (as in the closed-loop simulations)
% tauM from Table 1 (31 ms): fits the pulse runs better than the chirp's 18 ms (summed rms 10.1 vs 12.4 mm),
% mainly the coast-down of pulse_run2, whose fall rate is set by the actuator mass behind tauM
[plant.sys, plant.p] = plant_model(1, 0.66);
plant.dv = 0; plant.Fc = 0; plant.Fs = 0;
plant.drv = driver_map(); plant.drv.restick = true;
plant.coast0 = true;
plant.yMin = 0;
plant.tBreak = 0.05;   % [s] breakaway from the end stop: the ONE value fitted to a pulse run (pulse_run3, rms 1.65 mm)
plant.Tsens = 0.014; plant.tauSens = 0.0035;   % measured sensor: 14 ms update, 3.5 ms lag
end
