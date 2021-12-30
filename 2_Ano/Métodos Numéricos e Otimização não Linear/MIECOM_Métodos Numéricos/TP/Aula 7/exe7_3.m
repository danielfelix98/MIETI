clear all

x=[-1 -0.95 -0.85 -0.8 0.2 0.5 0.9];
f=[-1 -0.05 0.9 1 0.9 0.5 -0.3];

%a) e c)
[p2,r]=polyfit(x,f,2);

c0=[1 1 1];
[M,rM]=lsqcurvefit('MQ2',c0,x,f);

c0=[1 1];
[N,rN]=lsqcurvefit('MQ3',c0,x,f);

c0=[1 1 1];
[O,rO]=lsqcurvefit('MQ4',c0,x,f);

c0=[1 1];
[Q,rQ]=lsqcurvefit('MQ5',c0,x,f);

%b)
valP=polyval(x,f,2);
valM=MQ2(M,0.6)
valN=MQ3(N,0.6)
valO=MQ4(O,0.6)
valQ=MQ5(Q,0.6)

