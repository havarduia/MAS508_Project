
%Problem 2
m1=100; m2=25; b=1000; k1=25000; k2=3000;
%%
G1=tf([m1 b (k1+k2)],1);
G2=tf([m2 b k2],[b k2]);
G3=tf([b k2],1);
G4=tf(k1,1);
G=G4/(G1*G2-G3);
G_expanded=tf([k1*b k1*k2],[m1*m2 (m1+m2)*b (k1*m2+(m1+m2)*k2) k1*b k1*k2])
figure(1)
bode(G,'r',G_expanded,'--k')
figure(2)
step(G)