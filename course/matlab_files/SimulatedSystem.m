function dX = aug_sys(t,X,K,ifLearned,expl_noise_freq)
%% Function for the dynamic system 

x = X(1:4);

if ~ifLearned;   % Exploration activation function
	u = sum(sin(expl_noise_freq*t),2)-K*x;
else
	u = -K*x;    % If near-optimal controller is found
end

dx = dynamic_system(x,u);
dxx = kron(x',x')';
dux = kron(x',u')';
dX  = [dx;dxx;dux];
end


function dx = dynamic_system(x,u)
%% Dynamics of the linearized cart pol. 

A = [0    1     0     0;
    0    -6.85  2.70  0;
    0     0     0     1;
    0   -16.1  29.3   0];

B = [0
    50.7
    0;
    27.8];

dx = A*x+B*u;
end