function d = driver_map()
% DRIVER_MAP  Measured motor-driver map (Driver_test.slx, rig_driver_run1/2.mat, driver_map.png).
% Sliding: speed = up*(U - u0Up) for upward motion, dn*(U - u0Dn) downward [mm/s, V].
% Stuck while U stays inside [uLo, uHi]. Gains are relative to the linear model
% (kv/Ke = 29.2 mm/s per V), so plant input = g*(U - u0).
[~, p] = plant_model();
model = 1e3*p.kv/p.Ke;            % 29.2 mm/s per V
d.gUp = 29.7/model; d.u0Up = 0.104;
d.gDn = 20.1/model; d.u0Dn = 0.214;
d.uLo = -0.25; d.uHi = 0.35;
end
