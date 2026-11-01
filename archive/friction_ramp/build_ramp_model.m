function build_ramp_model()
% BUILD_RAMP_MODEL  Create Friction_ramp.slx: open-loop slow voltage ramps that
% find the breakaway voltages up and down (static friction) and the sliding
% voltage (Coulomb friction). Project_IOinterface.slx is left untouched.
% Run in R2025b. Afterwards: analyse_ramp on the exported run (see its help).
%
% Profile (total voltage, 0.3 V holds the load):
%   0-2 s hold, 2-22 s ramp up to 1.5 V, 24-44 s ramp down to -0.6 V, back to hold.
% Safety: once X passes 12 mm the voltage is limited to the 0.3 V hold for the
% rest of the run (latched), so the up-slide cannot run to the end of the stroke.

[tP, vP, xCut, vHold] = ramp_profile();
src = 'Project_IOinterface'; dst = 'Friction_ramp';
bdclose('all');
copyfile([src '.slx'], [dst '.slx'], 'f');
load_system(dst);
for b = {'U', 'Constant', sprintf('Pulse\nGenerator'), 'Sum1'}
  delete_block([dst '/' b{1}]);
end
l = find_system(dst, 'SearchDepth', 1, 'FindAll', 'on', 'Type', 'line');
for k = 1:numel(l)
  if get_param(l(k), 'SrcBlockHandle') < 0 || any(get_param(l(k), 'DstBlockHandle') < 0), delete_line(l(k)); end
end

add_block('simulink/Sources/Digital Clock', [dst '/Ramp time'], 'SampleTime', '1e-4');
add_block('simulink/Lookup Tables/1-D Lookup Table', [dst '/Ramp profile'], ...
  'BreakpointsForDimension1', mat2str(tP), 'Table', mat2str(vP), 'ExtrapMethod', 'Clip');
add_block('simulink/Discontinuities/Relay', [dst '/Cutoff latch'], ...   % off again only below -1 m = never
  'OnSwitchValue', num2str(xCut), 'OffSwitchValue', '-1', 'OnOutputValue', '1', 'OffOutputValue', '0');
add_block('simulink/Sources/Constant', [dst '/Hold voltage'], 'Value', num2str(vHold));
add_block('simulink/Math Operations/MinMax', [dst '/No more lift'], 'Function', 'min', 'Inputs', '2');
add_block('simulink/Signal Routing/Switch', [dst '/After cutoff'], 'Criteria', 'u2 > Threshold', 'Threshold', '0.5');
add_line(dst, 'Ramp time/1', 'Ramp profile/1', 'autorouting', 'on');
add_line(dst, 'Ramp profile/1', 'No more lift/1', 'autorouting', 'on');
add_line(dst, 'Hold voltage/1', 'No more lift/2', 'autorouting', 'on');
add_line(dst, 'No more lift/1', 'After cutoff/1', 'autorouting', 'on');
add_line(dst, 'Cutoff latch/1', 'After cutoff/2', 'autorouting', 'on');
add_line(dst, 'Ramp profile/1', 'After cutoff/3', 'autorouting', 'on');
add_line(dst, 'Sum/1', 'Cutoff latch/1', 'autorouting', 'on');     % 'Sum' = X [m]
add_line(dst, 'After cutoff/1', 'Gain/1', 'autorouting', 'on');    % -> existing limits and analog outputs
logPort([dst '/After cutoff'], 'U total');
logPort([dst '/Cutoff latch'], 'cut off');
set_param(dst, 'StopTime', num2str(tP(end)));
save_system(dst);
fprintf('%s.slx saved, stop time %g s\n', dst, tP(end));

%% Check: the same profile on the friction simulation, analysis must recover Fs and Fc
[sys1, p1] = plant_model(1.0, 1.0);
ctrl = load('controller_gains_v1.mat');
FcTrue = 14; FsTrue = 24;
plant = struct('sys', sys1, 'p', p1, 'dv', 0, 'Fc', FcTrue, 'Fs', FsTrue);
t = (0:ctrl.Ts:9*6)';
v = interp1(tP, vP, min(t, tP(end)));
out = simulate_loop(plant, ctrl, zeros(1, 9), struct('sigX', 22e-6, 'push', false, 'uOpen', v - vHold));
kCut = find(out.x > xCut, 1);          % second pass with the latch applied
v(kCut:end) = min(v(kCut:end), vHold);
out = simulate_loop(plant, ctrl, zeros(1, 9), struct('sigX', 22e-6, 'push', false, 'uOpen', v - vHold));
assert(max(out.y) < 0.025, 'ramp would run past the 25 mm stroke');
r = analyse_ramp(out.t, out.x, out.v);
fprintf('check: Fs %.1f N (true %d), Fc %.1f N (true %d), y max %.1f mm\n', r.Fs, FsTrue, r.Fc, FcTrue, 1e3*max(out.y));
assert(abs(r.Fs - FsTrue) < 3 && abs(r.Fc - FcTrue) < 3, 'analyse_ramp does not recover the simulated friction');
disp('Friction_ramp.slx is ready for the Speedgoat');
end

function logPort(blk, name)
ph = get_param(blk, 'PortHandles');
set_param(ph.Outport(1), 'DataLogging', 'on', 'DataLoggingNameMode', 'Custom', 'DataLoggingName', name);
end
