%% Example 3
K=8;
tau=0.3;
G3=tf(K,[tau 1]);
bode(G3)
%% Example 4
%Generating the plot for the question
J=0.011;
b=0.06;
k=6;
G4=tf(1,[J b k]);
[y,t]=impulse(G4,3);
figure
plot(t,y);
xlim([-1 3]);
hold on;
yline(0,'k--')
xlabel('time (s)');
ylabel('angular displacement');
box on;
grid on;
%Solution: see Lecture2_System_Modelling_part2.pdf slides 90, 91 and 92
t3=0.8744;
t1=0.3363;
O3=0.3576;
O1=1.564;
n=2;
Tosc=(t3-t1)/n; %Calculate oscilation period
wd=2*pi/Tosc; %Damped natural frequency
delta=1/2*log(O1/O3); %Logaritmic decrement
qsi=delta/sqrt(delta^2+(2*pi)^2); %Damping ratio
wn=wd/sqrt(1-qsi^2); %Undamped natural frequency

bcalculated=2*qsi*wn*J %Damping coefficient
kcalculated=J*wn^2 %Stiffness coefficient

%Compare calculated transfer function from experimental identification with
%initial transfer function used for ploting the impulse response
G4calculated=tf(1,[J bcalculated kcalculated]);
figure
bode(G4,'k',G4calculated,'r.-');
xlim([10^1 10^2]); %Zoom window to see the how close the aproximation is