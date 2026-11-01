function [levels, tFirst, tRec, tStep, xLo, xHi, rMid] = driver_levels()
%#codegen
% DRIVER_LEVELS  Settings of the driver test (shared by the model and analyse_driver).
% levels: total voltage U [V] of each open-loop step, alternating sides of the
% stuck band, small to large.
levels = [0.40 0.05 0.50 -0.05 0.60 -0.10 0.80 -0.20 1.00 -0.30 1.30 -0.50 1.60 -0.80 2.00 -1.20 0.30 0.10];
tFirst = 6;      % [s] controller lifts the payload to rMid first
tRec   = 3;      % [s] closed-loop re-centring before each step
tStep  = 0.4;    % [s] open-loop step length
xLo = 0.003; xHi = 0.021;   % [m] step aborted outside this band
rMid = 0.012;    % [m] hold position between steps (middle of the 25 mm stroke)
end
