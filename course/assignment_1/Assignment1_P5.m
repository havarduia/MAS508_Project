
%Problem 5
m=2;
b=8;
k=100;
G=tf(1,[m b k])
figure(1)
bode(G)
figure(2)
step(G);
roots([m b k]);
%%
%%Calculations see slide 33
wn=sqrt(k/m);
qsi=b/m/(2*wn);

Tp=pi/(wn*sqrt(1-qsi^2));
Ts=4/(qsi*wn);
OS=exp(-(qsi*pi/sqrt(1-qsi^2)))*100;
%from table slide 34 find normalised rise time
NTr=(qsi-0.2)/0.1*(1.321-1.205)+1.205;
Tr=NTr/wn;
step(G)