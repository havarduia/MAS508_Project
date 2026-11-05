
%% Extra Problem 2
num =[25.04 5.008];
den =[1 5.03247 25.1026 5.008];
G = tf(num,den);
% State-space model
[A,B,C,D] = tf2ss(num,den); %Obtain matrices A, B, C,D from the system
%transfer function numerator and denominator
S = ss(A,B,C,D);

%% Controlability test
n=size(A,2) %n=3
I=eye(n);
e=eig(A);
disp('Hautus controllability test');
for i=1:n
    rank([e(i)*I-A,B]) %=3
end

%% Observability test
disp('Hautus observability test');
n
for i=1:n
    rank([e(i)*I-A,B]) %=3
end
% System is fully controllable and fully observable
