function build_controller_model()
% BUILD_CONTROLLER_MODEL  Create Project_Controller.slx (Speedgoat) and
% Controller_test.slx (desktop check against the plant model).
% Project_IOinterface.slx is left untouched. Both generated files are
% overwritten on every run, so make manual edits in this script.

src = 'Project_IOinterface'; dst = 'Project_Controller'; tst = 'Controller_test';
models = fullfile(fileparts(fileparts(fileparts(mfilename('fullpath')))), 'models');
bdclose('all');
copyfile(fullfile(models, [src '.slx']), fullfile(models, [dst '.slx']), 'f');
load_system(dst);

% Remove the open-loop pulse-test wiring, keep the I/O interface
for b = {'U', 'Constant', sprintf('Pulse\nGenerator'), 'Sum1'}
  delete_block([dst '/' b{1}]);
end
deleteDanglingLines(dst);

addController([dst '/Controller']);
addReference(dst);
add_line(dst, 'Reference/1', 'Controller/1', 'autorouting', 'on');
add_line(dst, 'Sum/1', 'Controller/2', 'autorouting', 'on');   % 'Sum' = sensor - X0, labelled X [m]
% inverse driver map (identity when useInv = 0), see controller_params.m
add_block('simulink/User-Defined Functions/Fcn', [dst '/inverse driver'], 'Expr', ...
  'useInv*((u(1)>=0)*(u0Up + u(1)/gUp) + (u(1)<0)*(u0Dn + u(1)/gDn)) + (1-useInv)*u(1)');
add_line(dst, 'Controller/1', 'inverse driver/1', 'autorouting', 'on');
add_line(dst, 'inverse driver/1', 'Gain/1', 'autorouting', 'on');  % -> existing +-5 V limit and analog outputs
logPort([dst '/inverse driver'], 'U driver');
set_param(dst, 'PreLoadFcn', 'controller_params', 'InitFcn', 'controller_params');
save_system(dst);

%% Desktop test harness: same Controller subsystem, plant model instead of hardware
if bdIsLoaded(tst), close_system(tst, 0); end
if isfile(fullfile(models, [tst '.slx'])), delete(fullfile(models, [tst '.slx'])); end
new_system(tst);
set_param(tst, 'Solver', 'FixedStepDiscrete', 'FixedStep', 'Ts', 'StopTime', '14', ...
  'PreLoadFcn', 'controller_params', 'InitFcn', 'controller_params');
add_block([dst '/Controller'], [tst '/Controller']);
addReference(tst);
add_block('simulink/Sources/Constant', [tst '/vBias'], 'Value', 'vBias');
add_block('simulink/Math Operations/Sum', [tst '/minus bias'], 'Inputs', '+-');
add_block('simulink/Discrete/Discrete State-Space', [tst '/Plant'], ...
  'A', 'plantD.A', 'B', 'plantD.B', 'C', 'plantD.C', 'D', '0', 'InitialCondition', '[0; xRest; 0; xRest; 0]', 'SampleTime', 'Ts');   % at rest, like the rig
add_block('simulink/Sinks/Out1', [tst '/x']);
add_block('simulink/Sinks/Out1', [tst '/U']);
add_block('simulink/Sinks/Out1', [tst '/r']);
add_line(tst, 'Reference/1', 'Controller/1', 'autorouting', 'on');
add_line(tst, 'Controller/1', 'minus bias/1', 'autorouting', 'on');
add_line(tst, 'vBias/1', 'minus bias/2', 'autorouting', 'on');
add_line(tst, 'minus bias/1', 'Plant/1', 'autorouting', 'on');
add_line(tst, 'Plant/1', 'Controller/2', 'autorouting', 'on');
add_line(tst, 'Plant/1', 'x/1', 'autorouting', 'on');
add_line(tst, 'Controller/1', 'U/1', 'autorouting', 'on');
add_line(tst, 'Reference/1', 'r/1', 'autorouting', 'on');
logPort([tst '/Plant'], 'X [m]');   % same name as on the rig
Simulink.BlockDiagram.arrangeSystem(tst);
save_system(tst, fullfile(models, [tst '.slx']));

%% Check: nominal plant, both reference cases, no retuning
for rHigh = [0.015 0.020]
  assignin('base', 'rHigh', rHigh);
  evalin('base', 'controller_params');
  out = sim(tst, 'SaveOutput', 'on', 'OutputSaveName', 'yout', 'SaveFormat', 'Array');
  t = out.tout; x = out.yout(:, 1); U = out.yout(:, 2);
  errHigh = 1e3*(mean(x(t > 7.5 & t < 8)) - rHigh);
  errLow  = 1e3*(mean(x(t > 13.5)) - 0.005);
  fprintf('rHigh %2.0f mm: error at end of hold %.3f / %.3f mm, |U| max %.2f V\n', ...
    1e3*rHigh, errHigh, errLow, max(abs(U)));
  assert(abs(errHigh) < 0.05 && abs(errLow) < 0.05, 'Controller_test does not track the reference');
  assert(max(abs(U)) <= 5 + 1e-9, 'U exceeds the 5 V limit');
end

%% Check the chirp run and the FRF analysis: on the model plant it must recover the model
assignin('base', 'rHigh', 0.010); assignin('base', 'rLow', 0.010); assignin('base', 'aExc', 0.5);
assignin('base', 'aDither', 0);   % the 100 Hz dither would disturb the FRF estimate
evalin('base', 'controller_params');
out = sim(tst, 'StopTime', '66', 'SaveOutput', 'on', 'OutputSaveName', 'yout', 'SaveFormat', 'Array');
x = out.yout(:, 1); U = out.yout(:, 2);
fprintf('chirp run: x %.1f..%.1f mm, |U| max %.2f V\n', 1e3*min(x), 1e3*max(x), max(abs(U)));
assert(max(abs(U)) < 5, 'chirp drives U into the limit, lower aExc');
[f, Gm, Gmodel] = identify_frf(out.logsout);
band = f > 0.5 & f < 10;
relErr = abs(Gm(band) - Gmodel(band)) ./ abs(Gmodel(band));
fprintf('FRF check on the model plant: median error %.1f %%, max %.1f %% (0.5-10 Hz)\n', 100*median(relErr), 100*max(relErr));
assert(median(relErr) < 0.05, 'identify_frf does not recover the model plant');
evalin('base', 'clear rHigh rLow aExc aDither');
disp('Controller_test passed: Project_Controller.slx is ready for the Speedgoat');
end

function addController(ss)
% r, X in; U (total voltage incl. bias, limited to uLim, see controller_params.m) out.
% u = -K*xhat + Ke*xN, xN = integral of (r - X), clamped while saturated (anti-windup).
add_block('built-in/Subsystem', ss);
blk = @(lib, name, varargin) add_block(lib, [ss '/' name], varargin{:});
ln  = @(a, b) add_line(ss, a, b, 'autorouting', 'on');

blk('simulink/Sources/In1', 'r');
blk('simulink/Sources/In1', 'X');
blk('simulink/Sinks/Out1', 'U');
blk('simulink/Math Operations/Sum', 'error', 'Inputs', '+-');
blk('simulink/Signal Routing/Switch', 'anti-windup', 'Criteria', 'u2 ~= 0');
blk('simulink/Sources/Constant', 'zero', 'Value', '0');
blk('simulink/Discrete/Discrete-Time Integrator', 'xN', ...
  'IntegratorMethod', 'Integration: Forward Euler', 'SampleTime', 'Ts', 'InitialCondition', 'xN0');
blk('simulink/Math Operations/Gain', 'Ke', 'Gain', 'Ke');
blk('simulink/Discrete/Discrete State-Space', 'Observer', ...
  'A', 'Ao', 'B', 'Bo', 'C', 'eye(size(Ao, 1))', 'D', 'zeros(size(Ao, 1), 2)', ...
  'InitialCondition', 'xhat0', 'SampleTime', 'Ts');
blk('simulink/Signal Routing/Mux', 'Mux', 'Inputs', '2');
blk('simulink/Math Operations/Gain', 'K', 'Gain', 'K', 'Multiplication', 'Matrix(K*u)');
blk('simulink/Math Operations/Sum', 'uCmd', 'Inputs', '+-+');
% chirp excitation for frequency-response identification (zero unless aExc > 0) plus dither
blk('simulink/Sources/Digital Clock', 'clock', 'SampleTime', 'Ts');
blk('simulink/Math Operations/Bias', 'time since tExc', 'Bias', '-tExc');
blk('simulink/User-Defined Functions/Fcn', 'chirp', 'Expr', ...
  ['aExc*(u(1)>0)*(u(1)<tExcDur)*sin(2*pi*(fExc1*u(1) + (fExc2-fExc1)/(2*tExcDur)*u(1)^2))' ...
   ' + aDither*sin(2*pi*fDither*(u(1)+tExc))']);   % chirp + dither (controller_params.m)
blk('simulink/Sources/Constant', 'vBias', 'Value', 'vBias');
blk('simulink/Math Operations/Sum', 'plus bias', 'Inputs', '++');
blk('simulink/Discontinuities/Saturation', 'limit', 'UpperLimit', 'uLim(2)', 'LowerLimit', 'uLim(1)');
blk('simulink/Math Operations/Sum', 'minus bias', 'Inputs', '+-');
% anti-windup gate: hold the integrator when saturated AND the error pushes the same way
blk('simulink/Logic and Bit Operations/Relational Operator', 'saturated', 'Operator', '~=');
blk('simulink/Math Operations/Sign', 'sign e');
blk('simulink/Math Operations/Sign', 'sign u');
blk('simulink/Math Operations/Product', 'sign product');
blk('simulink/Logic and Bit Operations/Compare To Constant', 'same sign', 'relop', '>', 'const', '0');
blk('simulink/Logic and Bit Operations/Logical Operator', 'integrate', 'Operator', 'NAND');

ln('r/1', 'error/1');           ln('X/1', 'error/2');
ln('error/1', 'anti-windup/1'); ln('zero/1', 'anti-windup/3');
ln('anti-windup/1', 'xN/1');    ln('xN/1', 'Ke/1');
ln('Ke/1', 'uCmd/1');           ln('K/1', 'uCmd/2');
ln('clock/1', 'time since tExc/1'); ln('time since tExc/1', 'chirp/1'); ln('chirp/1', 'uCmd/3');
ln('uCmd/1', 'plus bias/1');    ln('vBias/1', 'plus bias/2');
ln('plus bias/1', 'limit/1');   ln('limit/1', 'U/1');
ln('limit/1', 'minus bias/1');  ln('vBias/1', 'minus bias/2');
ln('minus bias/1', 'Mux/1');    ln('X/1', 'Mux/2');      % observer gets the applied u
ln('Mux/1', 'Observer/1');      ln('Observer/1', 'K/1');
ln('plus bias/1', 'saturated/1'); ln('limit/1', 'saturated/2');
ln('error/1', 'sign e/1');      ln('uCmd/1', 'sign u/1');
ln('sign e/1', 'sign product/1'); ln('sign u/1', 'sign product/2');
ln('sign product/1', 'same sign/1');
ln('saturated/1', 'integrate/1'); ln('same sign/1', 'integrate/2');
ln('integrate/1', 'anti-windup/2');
Simulink.BlockDiagram.arrangeSystem(ss);

% log the signals for the Simulation Data Inspector / report
logPort([ss '/error'], 'error');  logPort([ss '/xN'], 'xN');
logPort([ss '/limit'], 'U total'); logPort([ss '/Observer'], 'xhat');
logPort([ss '/chirp'], 'excitation');
end

function addReference(sys)
% r = rLow + (rHigh - rLow)*pulse: rLow for 2 s, then rHigh / rLow for 6 s each,
% smoothed by the reference prefilter (controller_params.m). It starts at the payload's
% rest position xRest, so the first move to rLow is smooth too.
add_block('simulink/Sources/Pulse Generator', [sys '/pulse'], 'PulseType', 'Time based', ...
  'Amplitude', '1', 'Period', '12', 'PulseWidth', '50', 'PhaseDelay', '2');
add_block('simulink/Math Operations/Gain', [sys '/step size'], 'Gain', 'rHigh - rLow');
add_block('simulink/Sources/Constant', [sys '/rLow'], 'Value', 'rLow');
add_block('simulink/Math Operations/Sum', [sys '/reference step'], 'Inputs', '++');
add_block('simulink/Discrete/Discrete State-Space', [sys '/Reference'], 'A', 'preD.A', ...
  'B', 'preD.B', 'C', 'preD.C', 'D', 'preD.D', 'InitialCondition', 'xPre0', 'SampleTime', 'Ts');
add_line(sys, 'pulse/1', 'step size/1', 'autorouting', 'on');
add_line(sys, 'step size/1', 'reference step/1', 'autorouting', 'on');
add_line(sys, 'rLow/1', 'reference step/2', 'autorouting', 'on');
add_line(sys, 'reference step/1', 'Reference/1', 'autorouting', 'on');
end

function logPort(blockPath, name)
ph = get_param(blockPath, 'PortHandles');
set_param(ph.Outport(1), 'DataLogging', 'on', 'DataLoggingNameMode', 'Custom', 'DataLoggingName', name);
end

function deleteDanglingLines(sys)
lines = find_system(sys, 'SearchDepth', 1, 'FindAll', 'on', 'Type', 'line');
for h = lines'
  if get_param(h, 'SrcBlockHandle') == -1 || all(get_param(h, 'DstBlockHandle') == -1)
    delete_line(h);
  end
end
end
