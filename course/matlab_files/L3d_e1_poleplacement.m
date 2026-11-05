
% Example 1: Lecture 3d state stapce - pole place
close all;clc

% 
A=[0 1 0;  0 0 1; 3 -1 -5];
B=[0; 0; 1];

% Controllability matrix
Cab = ctrb(A,B)
Rank_c=rank(Cab)
% pole placement control
% solve for K using pole placement 
p1=-1;
p2=-2;
p3=-3;
P=[p1 p2 p3];
K=place(A,B,P)
% Closed-loop state-space control matric
A_cl = A-B*K;
 % check the poles of closed-loop system with u=-K*x
poles_cl=eig(A_cl) % verify the poles at the desired position

% Closed-loop state-space model
 C=[1 0 0 ; 0 1 0; 0 0 1];
 D=[0];
sys_cl = ss(A_cl,B,C,D);
 % find the poles of system
poles_cl=pole(sys_cl) % verify the poles at the desired position

% step respone 
figure(1);step(sys_cl,10); title('Step response of pole placement control');grid;

%  respone with initials

x0 = [1; 0; 0]; % Initial state
t = 0:0.01:10;
[y, t, x] = initial(sys_cl, x0, t);

% Extract control input u = -Kx from states
u = -x * K';

% Plotting
figure;
subplot(2,1,1);
plot(t, y(:,1), t, y(:,2), t, y(:,3),'LineWidth', 1.5);
title('System Output y(t)');
grid on;

subplot(2,1,2);
plot(t, u, 'r', 'LineWidth', 1.5);
title('Control Input u(t) = -Kx');
xlabel('Time (s)');grid;