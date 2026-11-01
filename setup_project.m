function setup_project()
% SETUP_PROJECT  Run once per MATLAB session (R2025b) from any folder: puts the project on the
% path and sends Simulink's generated files (.slxc, slprj, *_sg_rtw, .mldatx) to build/.
root = fileparts(mfilename('fullpath'));
addpath(fullfile(root, 'models'), fullfile(root, 'build'), ...
  genpath(fullfile(root, 'src')), genpath(fullfile(root, 'data')), ...
  fullfile(root, 'archive', 'design'), fullfile(root, 'archive', 'rig_runs'));
Simulink.fileGenControl('set', 'CacheFolder', fullfile(root, 'build'), ...
  'CodeGenFolder', fullfile(root, 'build'), 'createDir', true);
end
