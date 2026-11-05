%Problem 1
%Controller needs to yield <5% overshoot and a peak time of 0.3s
OS=5;
Tp=0.3;
zeta=-log(OS/100)/sqrt(pi^2+log(5/100)^2); %damping ratio zeta
omega_n=pi/(Tp*sqrt(1-zeta^2)); %damped frequency of the system

%characteristic equation
s=tf('s');
charac_eq=(s^2+2*zeta*omega_n*s+omega_n^2)*(s+10) %2nd order required
%response from OS and Tp, plus the additional pole to cancel the zero -10

%Calculate closed loop system matrix A-BK, and make
%the determinant of |sI-(A-BK)|=charac_eq
A=[0 1 0; 0 0 1; 0 -36 -15];
B=[0;0;1];
syms k1 k2 k3; %requires symbolic toolbox installed
syms S;
K=[k1 k2 k3];
A-B*K
%A-BK= [0 1 0; 0 0 1; -k1   -(36+k2)   -(15+k3)]
det(S*eye(3)-(A-B*K))
% ans = k1 + 36*S + k2*S + k3*S^2 + 15*S^2 + S^3
%We want to equal the coefficients from the determinate with the
%characteristic equation, then we can obtain the values of k1, k2 and k3
%|sI-(A-BK)|=s^3 + (15+k3)*s^2+(36+k2)*s+k1
%=> 29.97=15+k3
%=> 409.1=36+k2
%=>k1=2094
K=[2094 409.1-36 29.97-15]
