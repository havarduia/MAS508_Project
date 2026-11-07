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
for b = {'U', 'Pulse Generator', 'Step', 'Sum1'}
  delete_block([dst '/' b{1}]);
end
deleteDanglingLines(dst);
set_param([dst '/Saturation Input: [0, 5] V2'], 'Name', 'Saturation Input: [-5, 5] V2');   % its limits are [-5, 5]; old name was wrong

addController([dst '/Controller']);
addReference(dst);
add_line(dst, 'Reference/1', 'Controller/1', 'autorouting', 'on');
add_line(dst, 'Sum/1', 'Controller/2', 'autorouting', 'on');   % 'Sum' = sensor - X0, labelled X [m]
add_line(dst, 'Sum/1', 'Reference/2', 'autorouting', 'on');    % prefilter starts at the measured x
set_param(dst, 'StopTime', '36');   % = 3*tHold: low, high, low
add_line(dst, 'Controller/1', 'Saturation Input: [-5, 5] V2/1', 'autorouting', 'on');  % -> |u| + polarity analog outputs
embedParams(dst);
save_system(dst);

%% Desktop test harness: same Controller subsystem, plant model instead of hardware
if bdIsLoaded(tst), close_system(tst, 0); end
if isfile(fullfile(models, [tst '.slx'])), delete(fullfile(models, [tst '.slx'])); end
new_system(tst);
set_param(tst, 'Solver', 'FixedStepDiscrete', 'FixedStep', 'Ts', 'StopTime', '3*tHold', ...
  'PreLoadFcn', 'controller_params', 'InitFcn', 'controller_params');
add_block([dst '/Controller'], [tst '/Controller']);
addReference(tst);
add_block('simulink/Sources/Constant', [tst '/vBias'], 'Value', 'vBias');
add_block('simulink/Math Operations/Sum', [tst '/minus bias'], 'Inputs', '+-');
add_block('simulink/Discrete/Discrete State-Space', [tst '/Plant'], ...
  'A', 'plantD.A', 'B', 'plantD.B', 'C', 'plantD.C', 'D', '0', 'InitialCondition', '[0; xPlant0; 0; xPlant0; 0]', 'SampleTime', 'Ts');   % at rest, like the rig
add_block('simulink/Sinks/Out1', [tst '/x']);
add_block('simulink/Sinks/Out1', [tst '/U']);
add_block('simulink/Sinks/Out1', [tst '/r']);
add_line(tst, 'Reference/1', 'Controller/1', 'autorouting', 'on');
add_line(tst, 'Controller/1', 'minus bias/1', 'autorouting', 'on');
add_line(tst, 'vBias/1', 'minus bias/2', 'autorouting', 'on');
add_line(tst, 'minus bias/1', 'Plant/1', 'autorouting', 'on');
add_line(tst, 'Plant/1', 'Controller/2', 'autorouting', 'on');
add_line(tst, 'Plant/1', 'Reference/2', 'autorouting', 'on');
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
  tH = evalin('base', 'tHold');
  errHigh = 1e3*(mean(x(t > 2*tH - 0.5 & t < 2*tH)) - rHigh);
  errLow  = 1e3*(mean(x(t > 3*tH - 0.5)) - 0.005);
  fprintf('rHigh %2.0f mm: error at end of hold %.3f / %.3f mm, |U| max %.2f V\n', ...
    1e3*rHigh, errHigh, errLow, max(abs(U)));
  assert(abs(errHigh) < 0.05 && abs(errLow) < 0.05, 'Controller_test does not track the reference');
  assert(max(abs(U)) <= 5 + 1e-9, 'U exceeds the 5 V limit');
end

%% Check the start-up: the rest position changes between rig sessions (1.57-1.85 mm). The observer,
% integrator and prefilter start from the measured x, so a different rest must not kick the voltage.
for xp = [0.0016 0.00185 0.0010]
  assignin('base', 'rHigh', 0.015); evalin('base', 'controller_params'); assignin('base', 'xPlant0', xp);
  out = sim(tst, 'StopTime', '0.5', 'SaveOutput', 'on', 'OutputSaveName', 'yout', 'SaveFormat', 'Array');
  U = out.yout(:, 2); vB = evalin('base', 'vBias');
  fprintf('start at rest %.2f mm: |U - vBias| max %.2f V in the first 0.5 s\n', 1e3*xp, max(abs(U - vB)));
  assert(max(abs(U - vB)) < 1, 'start-up kick with the payload resting at %.2f mm', 1e3*xp);
end
evalin('base', 'clear xPlant0');

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
% Two blocks, same layout as the hand-tidied Project_Controller.slx:
%   ControlLaw_Observer   (uExc, yMeas, uSat, eInt -> uCmd): uCmd = Ke*xN - K*xhat + uExc
%   Saturation_AntiWindup (uCmd, r, yMeas -> uSat, eInt):    uSat = limit(uCmd + vBias),
%     eInt = r - X, or 0 while saturated AND the error pushes the same way (anti-windup)
add_block('built-in/Subsystem', ss);
co = [ss '/ControlLaw_Observer']; sa = [ss '/Saturation_AntiWindup'];
addControlLaw(co);
addSaturation(sa);
blk = @(lib, name, varargin) add_block(lib, [ss '/' name], varargin{:});
ln  = @(a, b) add_line(ss, a, b, 'autorouting', 'on');
blk('simulink/Sources/In1', 'r');
blk('simulink/Sources/In1', 'X');
blk('simulink/Sinks/Out1', 'U');
% chirp excitation for frequency-response identification (zero unless aExc > 0) plus dither
blk('simulink/Sources/Digital Clock', 'clock', 'SampleTime', 'Ts');
blk('simulink/Math Operations/Bias', 'time since tExc', 'Bias', '-tExc');
blk('simulink/User-Defined Functions/Fcn', 'chirp', 'Expr', ...
  ['aExc*(u(1)>0)*(u(1)<tExcDur)*sin(2*pi*(fExc1*u(1) + (fExc2-fExc1)/(2*tExcDur)*u(1)^2))' ...
   ' + aDither*sin(2*pi*fDither*(u(1)+tExc))']);   % chirp + dither (controller_params.m)
ln('clock/1', 'time since tExc/1'); ln('time since tExc/1', 'chirp/1');
O = 'ControlLaw_Observer'; S = 'Saturation_AntiWindup';
ln('chirp/1', [O '/1']); ln('X/1', [O '/2']); ln([S '/1'], [O '/3']); ln([S '/2'], [O '/4']);
ln([O '/1'], [S '/1']); ln('r/1', [S '/2']); ln('X/1', [S '/3']);
ln([S '/1'], 'U/1');
Simulink.BlockDiagram.arrangeSystem(ss);
logPort([ss '/chirp'], 'excitation');
end

function addControlLaw(ss)
add_block('built-in/Subsystem', ss);
blk = @(lib, name, varargin) add_block(lib, [ss '/' name], varargin{:});
ln  = @(a, b) add_line(ss, a, b, 'autorouting', 'on');
blk('simulink/Sources/In1', 'uExc');
blk('simulink/Sources/In1', 'yMeas');
blk('simulink/Sources/In1', 'uSat');
blk('simulink/Sources/In1', 'eInt');
blk('simulink/Sinks/Out1', 'uCmd');
blk('simulink/Discrete/Discrete-Time Integrator', 'xN', ...
  'IntegratorMethod', 'Integration: Forward Euler', 'SampleTime', 'Ts', 'InitialConditionSource', 'external');
blk('simulink/Math Operations/Gain', 'Ke', 'Gain', 'Ke');
% observer xhat[k+1] = Ao*xhat[k] + Bo*[u; x], written out so its start value can come from
% the measured x: at rest all positions equal x, velocities and current are 0 (xhat0 = x0map*x)
blk('simulink/Discrete/Delay', 'Observer', 'DelayLength', '1', 'InitialConditionSource', 'Input port', 'SampleTime', 'Ts');
blk('simulink/Math Operations/Gain', 'Ao', 'Gain', 'Ao', 'Multiplication', 'Matrix(K*u)');
blk('simulink/Math Operations/Gain', 'Bo', 'Gain', 'Bo', 'Multiplication', 'Matrix(K*u)');
blk('simulink/Math Operations/Sum', 'observer sum', 'Inputs', '++');
blk('simulink/Math Operations/Gain', 'xhat0', 'Gain', 'x0map');
% integrator starts at the value that holds that state: K*xhat0 = Ke*xN0
blk('simulink/Math Operations/Gain', 'xN0', 'Gain', 'K*x0map/Ke');
blk('simulink/Sources/Constant', 'vBias', 'Value', 'vBias');
blk('simulink/Math Operations/Sum', 'minus bias', 'Inputs', '+-');
blk('simulink/Signal Routing/Mux', 'Mux', 'Inputs', '2');
blk('simulink/Math Operations/Gain', 'K', 'Gain', 'K', 'Multiplication', 'Matrix(K*u)');
blk('simulink/Math Operations/Sum', 'command sum', 'Inputs', '+-+');
ln('eInt/1', 'xN/1');           ln('yMeas/1', 'xN0/1');   ln('xN0/1', 'xN/2');
ln('xN/1', 'Ke/1');             ln('Ke/1', 'command sum/1');
ln('K/1', 'command sum/2');     ln('uExc/1', 'command sum/3'); ln('command sum/1', 'uCmd/1');
ln('uSat/1', 'minus bias/1');   ln('vBias/1', 'minus bias/2');   % observer gets the applied u
ln('minus bias/1', 'Mux/1');    ln('yMeas/1', 'Mux/2');
ln('Mux/1', 'Bo/1');            ln('Observer/1', 'Ao/1');
ln('Ao/1', 'observer sum/1');   ln('Bo/1', 'observer sum/2');
ln('observer sum/1', 'Observer/1'); ln('Observer/1', 'K/1');
ln('yMeas/1', 'xhat0/1');       ln('xhat0/1', 'Observer/2');
Simulink.BlockDiagram.arrangeSystem(ss);
logPort([ss '/xN'], 'xN'); logPort([ss '/Observer'], 'xhat');
end

function addSaturation(ss)
add_block('built-in/Subsystem', ss);
blk = @(lib, name, varargin) add_block(lib, [ss '/' name], varargin{:});
ln  = @(a, b) add_line(ss, a, b, 'autorouting', 'on');
blk('simulink/Sources/In1', 'uCmd');
blk('simulink/Sources/In1', 'r');
blk('simulink/Sources/In1', 'yMeas');
blk('simulink/Sinks/Out1', 'uSat');
blk('simulink/Sinks/Out1', 'eInt');
blk('simulink/Math Operations/Sum', 'error', 'Inputs', '+-');
blk('simulink/Sources/Constant', 'vBias', 'Value', 'vBias');
blk('simulink/Math Operations/Sum', 'plus bias', 'Inputs', '++');
blk('simulink/Discontinuities/Saturation', 'limit', 'UpperLimit', 'uLim(2)', 'LowerLimit', 'uLim(1)');
% anti-windup gate: hold the integrator when saturated AND the error pushes the same way
blk('simulink/Signal Routing/Switch', 'anti-windup', 'Criteria', 'u2 ~= 0');
blk('simulink/Sources/Constant', 'zero', 'Value', '0');
blk('simulink/Logic and Bit Operations/Relational Operator', 'saturated', 'Operator', '~=');
blk('simulink/Math Operations/Sign', 'sign e');
blk('simulink/Math Operations/Sign', 'sign u');
blk('simulink/Math Operations/Product', 'sign product');
blk('simulink/Logic and Bit Operations/Compare To Constant', 'same sign', 'relop', '>', 'const', '0');
blk('simulink/Logic and Bit Operations/Logical Operator', 'integrate', 'Operator', 'NAND');
ln('r/1', 'error/1');           ln('yMeas/1', 'error/2');
ln('uCmd/1', 'plus bias/1');    ln('vBias/1', 'plus bias/2');
ln('plus bias/1', 'limit/1');   ln('limit/1', 'uSat/1');
ln('plus bias/1', 'saturated/1'); ln('limit/1', 'saturated/2');
ln('error/1', 'sign e/1');      ln('uCmd/1', 'sign u/1');
ln('sign e/1', 'sign product/1'); ln('sign u/1', 'sign product/2');
ln('sign product/1', 'same sign/1');
ln('saturated/1', 'integrate/1'); ln('same sign/1', 'integrate/2');
ln('error/1', 'anti-windup/1'); ln('integrate/1', 'anti-windup/2'); ln('zero/1', 'anti-windup/3');
ln('anti-windup/1', 'eInt/1');
Simulink.BlockDiagram.arrangeSystem(ss);
logPort([ss '/error'], 'error'); logPort([ss '/limit'], 'U total');
end

function addReference(sys)
% r = rLow + (rHigh - rLow)*pulse: rLow, rHigh, rLow for tHold s each, smoothed by the reference
% prefilter. The prefilter starts at the payload's measured rest position (input 2), so the
% first move to rLow is smooth wherever the payload rests.
add_block('simulink/Sources/Pulse Generator', [sys '/pulse'], 'PulseType', 'Time based', ...
  'Amplitude', '1', 'Period', '2*tHold', 'PulseWidth', '50', 'PhaseDelay', 'tHold');
add_block('simulink/Math Operations/Gain', [sys '/step size'], 'Gain', 'rHigh - rLow');
add_block('simulink/Sources/Constant', [sys '/rLow'], 'Value', 'rLow');
add_block('simulink/Math Operations/Sum', [sys '/reference step'], 'Inputs', '++');
ref = [sys '/Reference'];
add_block('built-in/Subsystem', ref);
blk = @(lib, name, varargin) add_block(lib, [ref '/' name], varargin{:});
ln  = @(a, b) add_line(ref, a, b, 'autorouting', 'on');
blk('simulink/Sources/In1', 'step');
blk('simulink/Sources/In1', 'X');
blk('simulink/Sinks/Out1', 'r');
% prefilter state z[k+1] = A z + B*step, r = C z + D*step; z0 = preMap*x (steady state at x)
blk('simulink/Discrete/Delay', 'state', 'DelayLength', '1', 'InitialConditionSource', 'Input port', 'SampleTime', 'Ts');
blk('simulink/Math Operations/Gain', 'A', 'Gain', 'preD.A', 'Multiplication', 'Matrix(K*u)');
blk('simulink/Math Operations/Gain', 'B', 'Gain', 'preD.B', 'Multiplication', 'Matrix(K*u)');
blk('simulink/Math Operations/Sum', 'state sum', 'Inputs', '++');
blk('simulink/Math Operations/Gain', 'C', 'Gain', 'preD.C', 'Multiplication', 'Matrix(K*u)');
blk('simulink/Math Operations/Gain', 'D', 'Gain', 'preD.D');
blk('simulink/Math Operations/Sum', 'output sum', 'Inputs', '++');
blk('simulink/Math Operations/Gain', 'z0', 'Gain', 'preMap');
ln('step/1', 'B/1'); ln('state/1', 'A/1'); ln('A/1', 'state sum/1'); ln('B/1', 'state sum/2');
ln('state sum/1', 'state/1'); ln('X/1', 'z0/1'); ln('z0/1', 'state/2');
ln('state/1', 'C/1'); ln('step/1', 'D/1'); ln('C/1', 'output sum/1'); ln('D/1', 'output sum/2');
ln('output sum/1', 'r/1');
Simulink.BlockDiagram.arrangeSystem(ref);
add_line(sys, 'pulse/1', 'step size/1', 'autorouting', 'on');
add_line(sys, 'step size/1', 'reference step/1', 'autorouting', 'on');
add_line(sys, 'rLow/1', 'reference step/2', 'autorouting', 'on');
add_line(sys, 'reference step/1', 'Reference/1', 'autorouting', 'on');
end

function embedParams(mdl)
% Put project_controller_workspace.m into the model workspace (Data source: MATLAB Code, saved
% inside the .slx), so Project_Controller.slx opens and runs on its own. The code recomputes the
% design from the physical parameters; check that it gives the gains and values in
% controller_gains_v3a.mat / controller_params.m.
code = fileread(which('project_controller_workspace.m'));
ws = runCode(code);
controller_params;   % reference values (this function's workspace: no base overrides)
for n = {'K', 'Ke', 'Ao', 'Bo', 'x0map', 'preMap', 'tHold', 'vBias', 'uLim', 'Ts', 'rHigh', 'rLow', ...
         'aExc', 'tExc', 'tExcDur', 'fExc1', 'fExc2', 'aDither', 'fDither'}
  ref = eval(n{1}); got = ws.(n{1});
  assert(isequal(size(got), size(ref)) && max(abs(got(:) - ref(:))) <= 1e-9*max(1, max(abs(ref(:)))), ...
    'project_controller_workspace.m: %s differs from controller_params/controller_gains', n{1});
end
assert(max(abs(ws.preD.A(:) - preD.A(:))) < 1e-12, 'prefilter differs');
mws = get_param(mdl, 'ModelWorkspace');
mws.DataSource = 'MATLAB Code';
mws.MATLABCode = code;
mws.reload;
set_param(mdl, 'PreLoadFcn', '', 'InitFcn', '');
note = Simulink.Annotation([mdl '/note']);
note.Text = sprintf(['Self-contained: all parameters are MATLAB code in the Model Workspace (Model Explorer).\n' ...
  'Test case: rHigh = 0.015 (15 -> 5 mm) or 0.020 (20 -> 5 mm), same gains.\n' ...
  'Source: src/design/project_controller_workspace.m, copied in by build_controller_model.m.']);
end

function ws = runCode(code)
% run the workspace code in its own workspace and return its variables as a struct
eval(code);
clear code
v = who; ws = struct();
for k = 1:numel(v), ws.(v{k}) = eval(v{k}); end
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
