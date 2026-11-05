%close all; clc
% example 4.  L3  pole placement reference tracking controol
% compare Pre-filter and Integral control 
% pole placement
A=[0 1; -3 -5]; B=[0; 1]; C=[1 0];D=0;

% 2nd system requiremtns
os=0.1; % required OS%
Ts=0.5; % settling time
zeta=-log(os)/(sqrt(pi^2+(log(os))^2))
omega=4/(zeta*Ts)
s= tf('s');
cha=s^2+2*zeta*omega*s+omega^2
P=roots([1 2*zeta*omega omega^2]) 
% solve for K using pole placement 

K=place(A,B, P)

% Closed-loop state-space model
Acl = A-B*K;
TF_CL = ss(Acl,B,C,D);


% Design pre-filter using DC gain
% solve for DC gain
 Kdc=dcgain(TF_CL);
 N=1/Kdc;

% Design pre-filter using equation
V = (C*(B*K-A)^(-1)*B)^(-1);
% Ckeck step response
figure(1);step(V*TF_CL,5);title('Step response with pole polacement');grid;
legend('Pre-filter');
[y1,t1]  = step(V*TF_CL,5);

%add integral control 
A1=[0 1; -3 -5]; B1=[0;1];C1=[1 0];
% Add an integral control
Ai = [ A1 [0 0]'; -C1 0];
Bi = [B1; 0];
Ci=[C1 0];
% Desired poles of the closed-loop 
% characteristic equation of poles
p_add=-100;
Pi = [P; p_add];
% solve for Ki=[K -K_e] using pole placement 
Ki=place(Ai,Bi, Pi)


% Closed-loop state-space model
A2 = [ A-B*[Ki(1) Ki(2)] -B*Ki(3); -C 0];
B2 = [0;0;1];
C2=[C 0];D2=0;
TF_CL2 = ss(A2,B2,C2,D2);

% Ckeck  step response
figure(2);step(TF_CL2,5);title('Step response with pole polacement');grid;legend('Integral control');
[y2,t2]  = step(TF_CL2,5);

figure(3); plot(t1(:,1),y1(:,1),t2(:,1),y2(:,1));
title('Step response with pole polacement');grid;legend('Pre-filter','Integral control');


% % Plot results after Simulink simulation
% figure(4);plot(out.time, out.signals(1).values, out.time, out.signals(2).values, out.time, out.signals(3).values )
% legend('Integral Pole Placement', 'Pre-filter Pole placement', 'reference value')
% 

% calculate K and ke
% syms s k1 k2 ke
% K=[k1 k2]
% Ae=[A-B*K B*ke; -C 0]
% det(s*eye(3)-Ae)
% cha=(s*s+16*s+183.1)*(s+100)



