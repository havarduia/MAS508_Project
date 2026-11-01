function build_driver_test()
% BUILD_DRIVER_TEST  Create Driver_test.slx (Speedgoat) and Driver_test_sim.slx (desktop check).
% Measures the motor driver's voltage -> speed map: the LQG controller from
% Project_Controller.slx holds the payload at 12 mm, and every 3.4 s the voltage
% is replaced by one constant level for 0.4 s (driver_levels.m). Run in R2025b
% after build_controller_model, with useInv = 0 in the workspace (this model has no
% inverse driver block). Afterwards: analyse_driver on the exported run.

src = 'Project_IOinterface'; dst = 'Driver_test'; tst = 'Driver_test_sim';
bdclose('all');
load_system('Project_Controller');
copyfile([src '.slx'], [dst '.slx'], 'f');
load_system(dst);
for b = {'U', 'Constant', sprintf('Pulse\nGenerator'), 'Sum1'}
  delete_block([dst '/' b{1}]);
end
l = find_system(dst, 'SearchDepth', 1, 'FindAll', 'on', 'Type', 'line');
for k = 1:numel(l)
  if get_param(l(k), 'SrcBlockHandle') < 0 || any(get_param(l(k), 'DstBlockHandle') < 0), delete_line(l(k)); end
end
addDriverTest([dst '/Driver test']);
add_line(dst, 'Sum/1', 'Driver test/1', 'autorouting', 'on');    % 'Sum' = X [m]
add_line(dst, 'Driver test/1', 'Gain/1', 'autorouting', 'on');   % -> existing limits and analog outputs
[levels, tFirst, tRec, tStep] = driver_levels();
stopTime = tFirst + numel(levels)*(tRec + tStep) + 2;
set_param(dst, 'StopTime', num2str(stopTime), 'PreLoadFcn', 'controller_params', 'InitFcn', 'controller_params');
save_system(dst);
fprintf('%s.slx saved, stop time %g s\n', dst, stopTime);

%% Desktop harness: same subsystem, nominal plant model instead of hardware
if bdIsLoaded(tst), close_system(tst, 0); end
if exist([tst '.slx'], 'file'), delete([tst '.slx']); end
new_system(tst);
set_param(tst, 'Solver', 'FixedStepDiscrete', 'FixedStep', 'Ts', 'StopTime', num2str(stopTime), ...
  'PreLoadFcn', 'controller_params', 'InitFcn', 'controller_params');
add_block([dst '/Driver test'], [tst '/Driver test']);
add_block('simulink/Sources/Constant', [tst '/vBias'], 'Value', 'vBias');
add_block('simulink/Math Operations/Sum', [tst '/minus bias'], 'Inputs', '+-');
add_block('simulink/Discrete/Discrete State-Space', [tst '/Plant'], ...
  'A', 'plantD.A', 'B', 'plantD.B', 'C', 'plantD.C', 'D', '0', 'SampleTime', 'Ts');
add_line(tst, 'Driver test/1', 'minus bias/1', 'autorouting', 'on');
add_line(tst, 'vBias/1', 'minus bias/2', 'autorouting', 'on');
add_line(tst, 'minus bias/1', 'Plant/1', 'autorouting', 'on');
add_line(tst, 'Plant/1', 'Driver test/1', 'autorouting', 'on');
logPort([tst '/Plant'], 'X [m]');
Simulink.BlockDiagram.arrangeSystem(tst);
save_system(tst);

%% Check: on the linear model the measured speeds must match the model line
evalin('base', 'controller_params');
out = sim(tst);
g = @(n) out.logsout.getElement(n).Values;
X = g('X [m]');
T = analyse_driver(X.Time, squeeze(X.Data), squeeze(g('U applied').Data), squeeze(g('step active').Data));
x = squeeze(X.Data);
fprintf('X range %.1f..%.1f mm, %d of %d steps ran\n', 1e3*min(x), 1e3*max(x), height(T), numel(levels));
assert(height(T) == numel(levels), 'not every step ran');
big = abs(T.model_mm_s) > 5;
relErr = abs(T.speed_mm_s(big) - T.model_mm_s(big)) ./ abs(T.model_mm_s(big));
fprintf('speed vs model: median error %.1f %%, max %.1f %%\n', 100*median(relErr), 100*max(relErr));
assert(median(relErr) < 0.15, 'analyse_driver does not recover the model speeds');
disp('Driver_test.slx is ready for the Speedgoat');
end

function addDriverTest(ss)
% X in; U (total voltage) out. Controller holds rMid, driver_schedule swaps in the steps.
add_block('built-in/Subsystem', ss);
blk = @(lib, name, varargin) add_block(lib, [ss '/' name], varargin{:});
ln  = @(a, b) add_line(ss, a, b, 'autorouting', 'on');
blk('simulink/Sources/In1', 'X');
blk('simulink/Sinks/Out1', 'U');
blk('simulink/Sources/Digital Clock', 'clock', 'SampleTime', 'Ts');
blk('simulink/User-Defined Functions/MATLAB Function', 'schedule');
chart = find(sfroot, '-isa', 'Stateflow.EMChart', 'Path', [ss '/schedule']);
chart.Script = sprintf(['function [active, vStep, rCtrl] = schedule(t, X)\n' ...
  '[active, vStep, rCtrl] = driver_schedule(t, X);\n']);
add_block('Project_Controller/Controller', [ss '/Controller']);
blk('simulink/Signal Routing/Switch', 'step or control', 'Criteria', 'u2 > Threshold', 'Threshold', '0.5');
ln('clock/1', 'schedule/1');        ln('X/1', 'schedule/2');
ln('schedule/3', 'Controller/1');   ln('X/1', 'Controller/2');
ln('schedule/2', 'step or control/1'); ln('schedule/1', 'step or control/2');
ln('Controller/1', 'step or control/3');
ln('step or control/1', 'U/1');
Simulink.BlockDiagram.arrangeSystem(ss);
logPort([ss '/step or control'], 'U applied');
ph = get_param([ss '/schedule'], 'PortHandles');
names = {'step active', 'step level'};
for k = 1:2
  set_param(ph.Outport(k), 'DataLogging', 'on', 'DataLoggingNameMode', 'Custom', 'DataLoggingName', names{k});
end
end

function logPort(blk, name)
ph = get_param(blk, 'PortHandles');
set_param(ph.Outport(1), 'DataLogging', 'on', 'DataLoggingNameMode', 'Custom', 'DataLoggingName', name);
end
