clear all

x=[0 5 10 15 20 30];
f=[0 106.8 227.04 362.78 517.35 901.67];

%a)
p3=polyfit(x(1:4),f(1:4),3);
estp3=polyval(p3,8);

%b)
x3=0:1:15;
f3=polyval(p3,x3);
plot(x,f,'o',x3,f3,'b')

