function [tP, vP, xCut, vHold] = ramp_profile()
% RAMP_PROFILE  Voltage profile of the friction ramp test (shared by
% build_ramp_model and analyse_ramp). vP is the total voltage [V].
tP = [0 2 22 23 24 44 46 50];
vP = [0.3 0.3 1.5 0.3 0.3 -0.6 0.3 0.3];
xCut = 0.012;    % X [m] above which the lift is cut off (latched)
vHold = 0.3;     % holding voltage
end
