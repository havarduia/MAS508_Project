%% Problem 1
s=tf('s'); %define s operator

G1=200/(s*(s^3+6*s^2+11*s+6))
G=feedback(G1,1);
%nyquist(G2);
zero(G) %zeros
pole(G) %poles
pzmap(G); grid on;
bode(G)

%% Problem 2
s=tf('s'); %define s operator
K=1; % set gain 0 dB (unity gain)
G1=K*(s+20)/(s*(s+2)*(s+3));
rlocus(G1)

%% Problem 3
A=[0 1 3; 2 2 4; 1 -4 3];
eig(A)
B=[0;1;0];
C=[1 1 0];
D=0;
sys1=ss(A,B,C,D)
%bode(sys1)
figure;pzmap(sys1)
%step(sys1)

%% Problem 4
s=tf('s'); %define s operator
K=1;
G1=K/((s+1)*(s+3)*(s+4));
figure
hold on;
subplot(2,1,1)
K=20;
G2=K/((s+1)*(s+3)*(s+4));
G2=feedback(G2,1);
step(G2);
title('Step response K=20');
subplot(2,1,2)
K=200;
G2=K/((s+1)*(s+3)*(s+4));
G2=feedback(G2,1);
step(G2);
title('Step response K=200');
%%
s=tf('s');
K=1;
G1=K/((s+1)*(s+3)*(s+4));
rlocus(G1)
%%
figure
bode(G1); grid on;
%% Problem 5
s=tf('s');
K=1;
Gol=K/((s^2+2*s+4)*(s+2));
Gcl=feedback(Gol,1);
figure; margin(Gol);
% title('Bode diagram for open-loop, K=1');

