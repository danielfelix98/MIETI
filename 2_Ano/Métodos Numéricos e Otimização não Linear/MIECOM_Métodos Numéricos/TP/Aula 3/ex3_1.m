clear all

x=[5.0 5.1 5.2 5.3 5.4 5.5 5.6 5.7 5.8 5.9 6.0];
f=[0.0639 0.0800 0.0988 0.1203 0.1442 0.1714 0.2010 0.2330 0.2673 0.3036 0.3414];

%a)
p2=polyfit(x(4:6),f(4:6),2);

%b)
estimativap2=polyval(p2,5.44);

%c)
p5=polyfit(x(3:8),f(3:8),5);

%d)
estimativap5=polyval(p5,5.44);

%e)
p10=polyfit(x(1:10),f(1:10),10)

%f)
estimativap10=polyval(p10,5.44)