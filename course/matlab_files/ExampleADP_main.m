%% Off-policy learning-based ADP for inverted pendulum
% Emil Mühlbradt Sveen, PhD Fellow DeepCobot, University of Agder, 2024


%% Parameters configuration
close all;
clear all;
clc;

xn = 4;
un = 1;

% Set the weighting matrices for the cost function
Q = diag([1 1 1 1]);
R = diag([0.1]);

% Initialize the feedback gain matrix
Kinit  = [-2,2,-20,-2];  %Only if A is Hurwitz, K can be set as zero.
K = Kinit;
N  = 150;           %Length of the window, should be at least xn^2+2*xn*un
MaxIteration = 10;  %Max iteration times
T  = 0.01;          %Length of each integration interval

x0 = [1;0;0;0]; %Initial condition

expl_noise_freq = (rand(un,100)-0.5)*1.5; % Exploration noise frequencies


% Matrices to collect online data and perform learning
Dxx=[];
Ixx=[];
Ixu=[];

% Initial condition of the augmented system
X=[x0;kron(x0',x0')';kron(x0,zeros(un,1))]';

%% Run the simulation and obtain the data matrices \delta_{xx},
%I_{xx}, and I_{xu}

ifLearned = 0;

x_save=[];
t_save=[];

for i=1:N
    % Simulation the system and at the same time collect online info.
    [t,X] = ode45(@(t,x)SimulatedSystem(t,x,K,ifLearned,expl_noise_freq), ...
        [(i-1)*T,i*T],X(end,:));
    
    %Append new data to the data matrices
    Dxx=[Dxx;kron(X(end,1:xn),X(end,1:xn))-kron(X(1,1:xn),X(1,1:xn))];
    Ixx=[Ixx;X(end,xn+1:xn+xn^2)-X(1,xn+1:xn+xn^2)];
    Ixu=[Ixu;X(end,xn+xn^2+1:end)-X(1,xn+xn^2+1:end)];
    
    % Keep track of the system trajectories
    x_save=[x_save;X];
    t_save=[t_save;t];
end

ifLearned = 1; % Mark learning finished

P_old = zeros(xn);
P = eye(xn)*10;    % Initialize the previous cost matrix
it = 0;            % Counter for iterations
p_save = [];       % Track the cost matrices in all the iterations
k_save = [];       % Track the feedback gain matrix in each iterations


%% Off-policy learning using the collected online data
while norm(P-P_old)>1e-8 & it<MaxIteration
    it = it+1;                        % Update and display the # of iters
    P_old = P;                        % Update the previous cost matrix
    QK = Q+K'*R*K;                    % Update the Qk matrix
    
    Theta = [Dxx,-Ixx*kron(eye(xn),K')-Ixu];  % Left-hand side of
    % the key equation
    Xi = -Ixx*QK(:);                 % Right-hand side of the key equation
    pp = pinv(Theta)*Xi;             % Solve the equations in the LS sense
    P = reshape(pp(1:xn*xn), [xn, xn]);  % Reconstruct the symmetric matrix
    P = (P + P')/2;
    
    BPv = pp(end-(xn*un-1):end);
    K = inv(R)*reshape(BPv,un,xn)/2;% Get the improved gain matrix
    p_save = [p_save,norm(P)];   % Keep track of the cost matrix
    k_save = [k_save,norm(K)];    % Keep track of the control gains
    
    disp(['K_', num2str(it), '=']);
    disp(K);
end

%% Post-learning simulations
[tt,xx]=ode45(@(t,x)SimulatedSystem(t,x,K,ifLearned,expl_noise_freq), ...
    [t(end) 10],X(end,:)');

% Keep track of the post-learning trajectories
t_final = [t_save;tt];
x_final = [x_save;xx];

% % For comparson, also get the unlearned simulation
% [ttt,xxx]=ode45(@(t,x)SimulatedSystem(t,x,Kinit,ifLearned,expl_noise_freq), ...
%     [t(end) 10],X(end,:)');
% t_unlearned = [t_save;ttt];
% x_unlearned = [x_save;xxx];

%% Plotting results
figure(1)
subplot(211)
plot(0:length(p_save)-1,p_save,'o',0:length(p_save)-1,p_save,'Linewidth',2);
ylim([-max(p_save)*0.2 max(p_save)*1.2]);
legend('||P_k||')
xlabel('Number of iterations')

subplot(212)
plot(0:length(k_save)-1,k_save,'^',0:length(k_save)-1,k_save,'Linewidth',2)
ylim([-max(k_save)*0.2 max(k_save)*1.2]);
legend('||K_k||')
xlabel('Number of iterations')

figure(2)
plot(t_final,x_final(:,1:4),'Linewidth',2)
legend('x_1','x_2','x_3','x_4')
grid on
xlabel('Time [s]')

% figure(3)
% plot(t_final, x_final(:,3),'k-', ...
%      ttt, xxx(:,3),'r--', ...
%     'Linewidth',2)
% % ylim([-400 150])
% grid on
% legend('Cart-Pole (Under ADP)', 'Cart Pole (Initial)')
% xlabel('Time [s]','FontSize',12)

figure(3)
plot(t_final, x_final(:,3),'k-','Linewidth',2)
grid on
legend('Cart-Pole $\theta$','interpreter','latex')
xlabel('Time [s]')

% figure(4)
% plot(expl_noise_freq(1,:))
% hold on
%plot(expl_noise_freq(2,:))


%% Display results
disp('Approximate Cost Matrix')
P
disp('Approximate Gain Matrix')
K

