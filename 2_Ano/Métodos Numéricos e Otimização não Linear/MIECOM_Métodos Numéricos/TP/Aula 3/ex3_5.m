clear all

x=[0 1 4 7 8 10 14];
f=[2.1 2.0 1.8 1.5 1.4 1.1 0];

%a)
p2=polyfit(x(3:5),f(3:5),2);

%b)
estp2=polyval(p2,5);

%c)
p5=polyfit(x(1:6),f(1:6),5);

%d)
estp5=polyval(p5,5);

%e)
p6=polyfit(x(1:7),f(1:7),6);

%f)
estp6=polyval(p6,5)

%g)
x2=4:0.1:8;
f2=polyval(p2,x2);
x5=0:0.1:10;
f5=polyval(p5,x5);
x6=0:0.1:14;
f6=polyval(p6,x6);
plot(x,f,'o',x2,f2,'r');
plot(x,f,'o',x5,f5,'b');
plot(x,f,'o',x6,f6,'g')