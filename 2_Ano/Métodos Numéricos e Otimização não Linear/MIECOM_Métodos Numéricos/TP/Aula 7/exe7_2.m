clear all

x=[1.2 1.75 1.1 2.0 0.5 0.8 1 1.5];
f=[16 18 16 19 10 11 14 16];

%a) e b)
[p2,r]=polyfit(x,f,2)

%c)
val=polyval(p2,1.6)
