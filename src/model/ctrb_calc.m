%% Check controlability and observability using Hautus test
n=size(A,2);
disp('Hautus controllability test');
for i=1:n
    rank([e(i)*eye(n)-A,B]) %=5
end

%% Observability test
disp('Hautus observability test');
n
for i=1:n
    rank([e(i)*eye(n)-A;C]) %=5
end

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%% How to avaoid rank-deficiency  using ctrb command
con=ctrb(A,B);
r=rank(con,0.01);% provide threshold to teh rank calculation. 