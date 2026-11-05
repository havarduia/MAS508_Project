
% Problem 3
%% a)
s=tf('s');
G=1/(s*(s+10));
omega_n=2;
zeta=0.7;

%Write G(s) in to the observable canonical form of minimum realization
A=[0 0; 1 -10]
B=[1;0];
C=[0 1];
D=[];
Plant=ss(A,B,C,D);
%Desired closed-loop characteristic polynomial
charac_eq=s^2+2*zeta*omega_n*s+omega_n^2
syms k1 k2; %requires symbolic toolbox installed
syms S;
K=[k1 k2];
A-B*K
%A-BK= [0 1 0; 0 0 1; -k1   -(36+k2)   -(15+k3)]
det(S*eye(2)-(A-B*K))
%We want to equal the coefficients from the determinate with the
%characteristic equation, then we can obtain the values of k1 and k2
%|sI-(A-BK)|=s^2+2.8s+4
%=> 10+k1=2.8
%=> 10*k1+k2=4
k1=2.8-10;
k2=4-10*k1;
K=[k1 k2]

%% b)
%Characteristic polynomial of observer (-10,-10) is
charac_obs=(s+10)^2
%Let L=[l1,l2]^T then the characteristic polynomial of (A-LC) is
syms L1 L2; %requires symbolic toolbox installed
syms S;
L=[L1;L2];
det(S*eye(2)-(A-L*C))
%|sI-(A-LC)|=charac_obs then
%=> 10+L2=20
%=> L1=100
L1=100;
L2=20-10;
L=[L1;L2]
%Then the state observer is designed as
%dx_o=(A-L*C)x_o+Bu+Ly
A-L*C