
%% Exercise 1 - Direct current (DC) motor (2nd-order system)
R=1;
L=0.0002;
Psi=0.04;
B=0.0001;
J=0.00005;

%% Transfer function / Step response
figure
set(0, 'DefaultLineLineWidth', 2); %Set thicker plot lines
tf1=tf([Psi],[J*L (J*R+B*L) B*R+Psi^2]); % Transfer function of the 2nd order system
step(tf1,0.5); %Plot step response
hold on;
out=sim('mas508_lab_cw36_exercise1'); %Make sure Simulink file is the working path
plot(out.ScopeData{1}.Values.Time,out.ScopeData{1}.Values.Data,'--r'); %Plot step response from Simulink data
legend('transfer function','block diagram')
%% Bode diagram
figure
bode(tf1); % Plot Bode diagram for tf1