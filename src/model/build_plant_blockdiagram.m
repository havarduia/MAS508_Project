function build_plant_blockdiagram()
% BUILD_PLANT_BLOCKDIAGRAM  Draw the plant model (plant_model.m) as a Simulink block diagram,
% one block group per equation (Lab 1/Lab 2 style), check it against plant_model and export
% figures/plant_blockdiagram.png. Illustration and check only: the design and Controller_test
% keep using plant_model. models/Plant_blockdiagram.slx is overwritten on every run.
%
%   KVL           L di/dt  = kv*v - R*i - kb*omega_m,   omega_m = N*ydot
%   torque/screw  F        = eta*N*ki*i
%   actuator      Me ydd   = F - Fs
%   spring        Fs       = ks*(y - x) + bs*(ydot - xdot)
%   payload       ml xdd   = Fs
%   sensor        xs       = x / (tauS*s + 1)

mdl = 'Plant_blockdiagram';
root = fileparts(fileparts(fileparts(mfilename('fullpath'))));
if bdIsLoaded(mdl), close_system(mdl, 0); end
new_system(mdl);
params = ['[~, p] = plant_model(1, 0.99, 0.018, 0.0106); kv = p.kv; R = p.R; L = p.L; ki = p.ki; kb = p.kb; ' ...
          'N = p.N; eta = p.eta; Me = p.Me; ks = p.ks; bs = p.bs; ml = p.ml; tauS = p.tauS;'];
set_param(mdl, 'PreLoadFcn', params, 'InitFcn', params, 'StopTime', '20');
evalin('base', params);

% blocks: name, library block, [x y], parameters
gain = 'simulink/Math Operations/Gain'; sumb = 'simulink/Math Operations/Sum';
intg = 'simulink/Continuous/Integrator';
B = {
  'v',         'simulink/Sources/In1',  [20 100],  {}
  'kv',        gain, [90 100],  {'Gain', 'kv'}
  'KVL',       sumb, [170 100], {'Inputs', '+--', 'IconShape', 'round'}
  '1/L',       gain, [240 100], {'Gain', '1/L'}
  'i',         intg, [320 100], {}
  'ki',        gain, [410 100], {'Gain', 'ki'}
  'eta*N',     gain, [500 100], {'Gain', 'eta*N'}
  'Newton actuator', sumb, [590 100], {'Inputs', '+-', 'IconShape', 'round'}
  '1/Me',      gain, [660 100], {'Gain', '1/Me'}
  'ydot',      intg, [750 100], {}
  'y',         intg, [860 100], {}
  'R',         gain, [240 190], {'Gain', 'R', 'Orientation', 'left'}
  'N',         gain, [660 20],  {'Gain', 'N', 'Orientation', 'left'}
  'kb',        gain, [320 20],  {'Gain', 'kb', 'Orientation', 'left'}
  'y - x',     sumb, [960 200], {'Inputs', '+-', 'IconShape', 'round'}
  'ydot - xdot', sumb, [960 280], {'Inputs', '+-', 'IconShape', 'round'}
  'ks',        gain, [1040 200], {'Gain', 'ks'}
  'bs',        gain, [1040 280], {'Gain', 'bs'}
  'spring force', sumb, [1120 240], {'Inputs', '++', 'IconShape', 'round'}
  '1/ml',      gain, [660 400], {'Gain', '1/ml'}
  'xdot',      intg, [750 400], {}
  'x',         intg, [860 400], {}
  'sensor',    'simulink/Continuous/Transfer Fcn', [990 400], {'Numerator', '1', 'Denominator', sprintf('[%g 1]', evalin('base', 'tauS'))}
  'x_meas',    'simulink/Sinks/Out1', [1110 400], {}
};
for k = 1:size(B, 1)
  w = 30; h = 30;
  if contains(B{k, 2}, 'Gain'), w = 50; h = 34; end          % wide enough to print the expression, not -K-
  if contains(B{k, 2}, 'Transfer'), w = 100; h = 50; end
  pos = [B{k, 3} - [w h]/2, B{k, 3} + [w h]/2];
  % names hidden except the ports: the gain icons and the signal labels already say what each block is
  showName = 'off'; if contains(B{k, 2}, {'In1', 'Out1'}), showName = 'on'; end
  add_block(B{k, 2}, [mdl '/' strrep(B{k, 1}, '/', '//')], 'Position', pos, 'ShowName', showName, B{k, 4}{:});
end

% lines: from block/port, to block/port, signal name ('' = none)
n = @(s) strrep(s, '/', '//');
W = {
  'v', 1, 'kv', 1, 'v'
  'kv', 1, 'KVL', 1, ''
  'KVL', 1, '1/L', 1, ''
  '1/L', 1, 'i', 1, 'di/dt'
  'i', 1, 'ki', 1, 'i'
  'ki', 1, 'eta*N', 1, 'T_m'
  'eta*N', 1, 'Newton actuator', 1, 'F'
  'Newton actuator', 1, '1/Me', 1, ''
  '1/Me', 1, 'ydot', 1, 'yddot'
  'ydot', 1, 'y', 1, 'ydot'
  'i', 1, 'R', 1, ''
  'R', 1, 'KVL', 2, 'R i'
  'ydot', 1, 'N', 1, ''
  'N', 1, 'kb', 1, 'omega_m'
  'kb', 1, 'KVL', 3, 'v_emf'
  'xdot', 1, 'x', 1, 'xdot'        % main lines before their branches, so each label is drawn once
  'x', 1, 'sensor', 1, 'x'
  'y', 1, 'y - x', 1, 'y'
  'x', 1, 'y - x', 2, ''
  'ydot', 1, 'ydot - xdot', 1, ''
  'xdot', 1, 'ydot - xdot', 2, ''
  'y - x', 1, 'ks', 1, ''
  'ydot - xdot', 1, 'bs', 1, ''
  'ks', 1, 'spring force', 1, ''
  'bs', 1, 'spring force', 2, ''
  'spring force', 1, 'Newton actuator', 2, 'F_s'
  'spring force', 1, '1/ml', 1, ''
  '1/ml', 1, 'xdot', 1, 'xddot'
  'sensor', 1, 'x_meas', 1, 'x_s'
};
for k = 1:size(W, 1)
  hl = add_line(mdl, sprintf('%s/%d', n(W{k, 1}), W{k, 2}), sprintf('%s/%d', n(W{k, 3}), W{k, 4}), 'autorouting', 'smart');
  if ~isempty(W{k, 5}), set_param(hl, 'Name', W{k, 5}); end
end
save_system(mdl, fullfile(root, 'models', [mdl '.slx']));

%% Check: same 1 V, 0.3 s pulse through the block diagram and through plant_model
t = (0:1e-4:20)'; u = double(t >= 2 & t < 2.3);
out = sim(mdl, 'SrcWorkspace', 'current', 'LoadExternalInput', 'on', 'ExternalInput', '[t, u]', 'SaveOutput', 'on', 'OutputSaveName', 'yout', ...
  'SaveFormat', 'Array', 'Solver', 'ode15s', 'RelTol', '1e-9', 'AbsTol', '1e-12', 'MaxStep', '1e-3', ...
  'OutputOption', 'SpecifiedOutputTimes', 'OutputTimes', 't');
xsSim = out.yout;
xsSs = lsim(plant_model(1, 0.99, 0.018, 0.0106), u, t, 'foh');
err = max(abs(xsSim - xsSs));
fprintf('block diagram vs plant_model, 1 V 0.3 s pulse: max |difference| = %.2e mm (travel %.2f mm)\n', 1e3*err, 1e3*xsSs(end));
assert(err < 1e-3*max(abs(xsSs)), 'block diagram does not match plant_model');

print(['-s' mdl], '-dpng', '-r300', fullfile(root, 'figures', 'plant_blockdiagram.png'));
close_system(mdl, 0);
end
