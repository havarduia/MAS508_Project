
%Problem 4
K=2;
tau=1/40;
G=tf([K],[tau 1])
figure(1)
step(G)
%%Calculate Settling Time and Rise Time
%(see Lecture3_SystemResponse slide 14)
Tr=2.2*tau;
Ts=4*tau;