function [active, vStep, rCtrl] = driver_schedule(t, X)
%#codegen
% DRIVER_SCHEDULE  Step schedule for Driver_test.slx (runs inside a MATLAB Function block).
% The LQG controller holds the payload at rMid; every tRec + tStep seconds the
% voltage is replaced by one constant level for tStep seconds (open loop).
% During a step the controller reference follows X, so its integrator does not wind up.
% A step ends early if X leaves [xLo, xHi] (keeps the actuator off the end stops).
[levels, tFirst, tRec, tStep, xLo, xHi, rMid] = driver_levels();
persistent aborted lastK
if isempty(aborted), aborted = false; lastK = -1; end
active = 0; vStep = 0; rCtrl = rMid;
k = floor((t - tFirst)/(tRec + tStep));
if t < tFirst || k >= numel(levels), return; end
if k ~= lastK, aborted = false; lastK = k; end
if t - tFirst - k*(tRec + tStep) >= tRec
  if X < xLo || X > xHi, aborted = true; end
  if ~aborted
    active = 1; vStep = levels(k + 1); rCtrl = X;
  end
end
end
