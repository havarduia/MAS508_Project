
%% Exercise 2 - Robot joint with elasticity (4nd-order system)
Jm=2; Bm=0.5; Jl=10; Bl=1; k=100;
% Parameters taken from Spong, M. W., Hutchinson, S. and Vidyasagar,
% M. Robot modeling and control. John Wiley & Sons, Inc. 2006.

%% Transfer function
tf1=tf([k],[(Jm*Jl) (Jm*Bl+Jl*Bm) (Jm*k+Jl*k+Bm*Bl) (Bm*k+Bl*k) 0]);

%alternative way to obtain transfer function (for verification)
pl=tf([Jl Bl k],[1]);
pm=tf([Jm Bm k],[1]);
G1=k/(pm*pl);
G2=-k;
tf2=feedback(G1,G2);


GG1=-1/k;
GG2=pl*pm/k;

tf3=feedback(GG1,GG2);


%% Step Response of tf1 and tf2
figure
set(0, 'DefaultLineLineWidth', 2); %Set thicker plot lines
step(tf1,5,'k'); %Plot step response for tf1
hold on
step(tf2,5,'--r'); %Plot step response for tf2
legend('tf1','tf2');
%% Bode diagram of tf1 and tf2
figure
bode(tf1,'k'); % Plot Bode diagram for tf1
hold on
bode(tf2,'--r'); % Plot Bode diagram for tf2
grid on
legend('tf1','tf2');