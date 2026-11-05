%% Extra Problem 1
% State-space model, states x = [x1, x2, x3]':
A = [0 1 0; 0 0 1; -6 -11 -6];
B = [0; 0; 1];
C = [4 5 1];
D = [];
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
% System is fully controllable and but e(1) is not observable because
% rank([e(1)*I-A,B])=2 and n=3
