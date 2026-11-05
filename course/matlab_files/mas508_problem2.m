% Problem 2
%% a) State-space matrices of the system
R=1; L=0.0002; qsi=0.04; B=0.0001; J=0.00005;

A=[-B/J qsi/J; -qsi/L -R/L];
B=[0;1/L];
C=[1 0];
D=0;
%% b) Evaluate the system's controllability
n=size(A,2) %n=2
I=eye(n);
e=eig(A);
disp('Hautus controllability test');
for i=1:n
    rank([e(i)*I-A,B]) %=2 the system is fully controllable
end

%% c) Design state feedback controller
s=tf('s');
C_p=2*e; %make new desired poles (C_p) twice faster than the open-loop system
charac_eq=(s-C_p(1))*(s-C_p(2))
%charac_eq=s^2+10004s+2e05
Plant=ss(A,B,C,D);

%Find the controllable companion matrices of system
S=sym('S')
det(S*eye(2)-A)
%%
Ac=[0 1; -170000 -5002]
Bc=[0;1]
Q=ctrb(A,B);
Qc=ctrb(Ac,Bc);
W=Q*inv(Qc)
%%
%Calculate closed loop system matrix A-BK, and make
%the determinant of |sI-(Ac-BcKc)|=charac_eq
charac_eq
syms k1 k2
Kc=[k1 k2];
det(S*eye(2)-(Ac-Bc*Kc))
%10004=5002+k2
%6.8e5=k1+170000
k1=6.8e5-170000;
k2=10004-5002;
Kc=[k1 k2]

%Convert gain for original system
K=Kc*inv(W)

%Alternatively using MATLAB function for pole placement
K = place(A,B,C_p) % State feedback gain
%we very that the K vector is the same, this is a good way
%to verify that matrices Ac, Bc, Kc and W were calculated correctly


%Closed-loop state-space model
Acl = A-B*K; % New system matrix with state-feedback 
ClLoop = ss(Acl,B,C,D); 

%% d) Compute prefilter V to ensure steady-state accuracy 
V = (C*(B*K-A)^(-1)*B)^(-1); 

%% e) MATLAB plot of step response for open-loop, closed-loop and
%closed-loop with pre-filter
figure
step(Plant, 'g', ClLoop, 'r', V*ClLoop, 'b', 1); %Step-response
hold on;
%Figure formating
legend('Plant','StateFeedback', 'StateFeedback+Prefilter');
grid on;

figure
%pzmap(S,'k',Sc,'g',So,'r');
h1=pzplot(Plant,'g');
opz = getoptions(h1);
set(h1.allaxes.Children(1).Children, 'MarkerSize', 16,'LineWidth',8)
hold on
h2=pzplot(ClLoop,'r');
opz = getoptions(h2);
set(h2.allaxes.Children(1).Children, 'MarkerSize', 16,'LineWidth',4)

legend('Plant','StateFeedback');
grid on
