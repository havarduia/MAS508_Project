%% MAS508-G Labs
% Support materials to the slides of Lab CW34

%% Example 1a - Plot signals from Simulink simulation in MATLAB
set(0, 'DefaultLineLineWidth', 1.5); %Set thicker plot lines
set(0,'DefaultAxesFontSize', 14); %Set default axes fontsize
set(0,'DefaultAxesFontName','Times'); %Set axes fontname

figure; %Create figure
hold on;
plot(ScopeData.time,ScopeData.signals(1).values); %Plot signals
plot(ScopeData.time,ScopeData.signals(2).values);
plot(ScopeData.time,ScopeData.signals(3).values);
plot(ScopeData.time,ScopeData.signals(4).values);
plot(ScopeData.time,ScopeData.signals(5).values);
legend(ScopeData.signals.label); %Add legend
xlim([0 2]); %Set window limits on x-axis
ylim([-1.5 2]); %Set window limits on y-axis
xlabel('Time [s]'); %x-axis label
ylabel('Signal'); %y-axis label
grid on; %Turn on grid lines

%% Example 1b - Signal from MATLAB to Simulink
t=0:1e-3:10;
signal=200*sin(2*pi*3*t);
F=timeseries(signal,t);

%% Example 2a - Mass-spring-damper system
%Parameters
m=11.2; %mass
k=1200; %stiffness
b=20; %damping
F=0; %force
Ts=1e-3; %solver timestep

%% Example 2c - Disturbance
t=0:1e-3:10;
disturbance=-0.1*sin(2*pi*100*t);
d=timeseries(disturbance,t);

%% Example 2c - Plot position and velocity from simulation
set(0, 'DefaultLineLineWidth', 1.5); %Set thicker plot lines
set(0,'DefaultAxesFontSize', 14); %Set default axes fontsize
set(0,'DefaultAxesFontName','Times'); %Set axes fontname

figure; %Create figure
subplot(2,1,1);
plot(ScopeData2.time,ScopeData2.signals(1).values); %Plot signals
xlabel('Time [s]'); %x-axis label
ylabel('Position [m]'); %y-axis label
hold on;
subplot(2,1,2);
plot(ScopeData2.time,ScopeData2.signals(2).values,'r');
xlabel('Time [s]'); %x-axis label
ylabel('Velocity [m/s]'); %y-axis label