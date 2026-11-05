
%% Example 2
% Model parameters
Jm = 1; %Motor inertia
Jl=0.5; %Load inertia
Bm=10; %Motor damping
Bl=1; %Load damping
k=1000; %Stiffness

% State-space model, states x = [load pos, load vel, motor pos, motor vel]':
A = [0 1 0 0; -k/Jl -Bl/Jl k/Jl 0; 0 0 0 1; k/Jm 0 -k/Jm -Bm/Jm];
B = [0 0 0 1/Jm]';
C = [1 0 0 0];
D = [];
S = ss(A,B,C,D);

%% Controlability test
n=size(A,2) %n=4
I=eye(n);
e=eig(A); %Eigenvalues of A: e = [  -2.3160 +54.5940i
                            %       -2.3160 -54.5940i
                            %       -7.3680 + 0.0000i
                            %       -0.0000 + 0.0000i]
disp('Hautus controllability test');
for i=1:n
    rank([e(i)*I-A,B]) %=4
end

%% Observability test
disp('Hautus observability test');
n
for i=1:n
    rank([e(i)*I-A;C]) %=4
end
% System is fully controllable and fully observable

%% Compute transformation matrix
%Controllability matrix can be obtained with the MATLAB function ctrb() or
%can be also inputed as Cr=[B A*B A^2*B A^3*B] (for n=4)
Cr = ctrb(A,B);
%Inverse of Cr matrix (Cr^-1)
Cr_inv=inv(Cr);
%Get the last row of the Cr^-1 matrix in reverse order
c1=Cr_inv(end,:); 
% note: this can be done in different ways
%       c1=Cr_inv(end,:) returns the the full collumn (:) of the row n
%                       and then inverts the array order

%Build the inverse T matrix (T^-1)
T_inv = [c1; c1*A; c1*A^2; c1*A^3];
%Get the T matrix
T=inv(T_inv);

% note: we can now use the T matrix to transform our state-space model
% in the Controllable canonical form as Sc = ss(Ac,Bc,Cc,Dc). The matrices
% for the controllable canonical form are then given by
Ac = T^(-1)*A*T;
Bc = T^(-1)*B;
Cc = C*T;
Dc = D;
Sc = ss(Ac,Bc,Cc,Dc);

%% Example 3 - Observable canonical form
% from the duality principle, one can obtain the state-space system in
%observable canonical form So = ss(Ao,Bo,Co,Do) from the previously
%obtained controllable canonical form
Ao = Ac';
Bo = Cc';
Co = Bc';
Do = Dc;
So = ss(Ao,Bo,Co,Do);

% Compare impulse response, eigenvalues, bode response, pzmap to verify
% that all of these matrices represent the exact same system
%% Impulse response
figure
impulse(S,'b',Sc,'r',So,'y'); %Impulse response
legend('Original s-s model','Controlable canonical form','Observable canonical form')
grid on

%% Eigenvalues
e_A=eig(A)
e_Ac=eig(Ac)
e_Ao=eig(Ao) %Compare eigenvalues

%% Bode response
figure
bode(S,'b',Sc,'r',So,'--y');
legend('Original s-s model','Controlable canonical form','Observable canonical form')
grid on

%% Pole-zero map
figure
%pzmap(S,'k',Sc,'g',So,'r');
h1=pzplot(S,'b');
opz = getoptions(h1);
set(h1.allaxes.Children(1).Children, 'MarkerSize', 24,'LineWidth',8)
hold on
h2=pzplot(Sc,'r');
opz = getoptions(h2);
set(h2.allaxes.Children(1).Children, 'MarkerSize', 16,'LineWidth',4)
hold on
h2=pzplot(So,'y');
opz = getoptions(h2);
set(h2.allaxes.Children(1).Children, 'MarkerSize', 8,'LineWidth',2)
legend('Original s-s model','Controlable canonical form','Observable canonical form')
grid on



