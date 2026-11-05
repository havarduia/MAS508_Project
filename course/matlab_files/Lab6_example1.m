%% Example 1
% State-space model, state-vector x = [\xi_1 \xi_2]':
% Define system matrices A, B, C and D
A = [-1 0; -1 -2];
B = [2; -1];
C = [1 1];
D = [];
% Create ss object (state-space model)
S = ss(A,B,C,D);

%% Controlability test
n=size(A,2) %n=2
I=eye(n);
e=eig(A); %Eigenvalues of A: e=[-2; -1]
disp('Controllability test');
for i=1:n
    rank([e(i)*I-A,B]) %=n for controllable
end
%Since for each eigenvalue e(i) the condiction rank([e(i)*I-A,B]) = n is
%verified, we can conclude that the system is fully controllable

%% Observability
disp('Observability test');
for i=1:n
    rank([e(i)*I-A;C]) %=n for observable
end
%Since the condition rank([e(i)*I-A;C])=n is not valid for e(2), we can
%conclude that the eigenvalue e(2)=-1 is not observable