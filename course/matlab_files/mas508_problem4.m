

% Problem 4
A=[0 1 0; 0 0 1; -1 -5 -6];
B=[0;1;1];
C=[0 0 1];
D=[];
Plant=ss(A,B,C,D);
%Desired poles
p=[-2+4i;-2-4i;-10];

K=place(A,B,p)

%Closed-loop state-space model
Acl = A-B*K; % New system matrix with state-feedback 
ClLoop = ss(Acl,B,C,D);

figure
step(Plant,'b',10);
hold on
step(ClLoop,'r',10);
