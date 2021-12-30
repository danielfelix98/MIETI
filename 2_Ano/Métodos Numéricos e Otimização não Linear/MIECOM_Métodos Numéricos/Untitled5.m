clear all;
clc;
x=[0,0.1,0.2,0.3,0.4,0.5,0.6,3.6,6.6,9.6,9.8,10]
f=[0,0.1,0.2,0.3,0.4,0.5,0.6,0.6,0.6,0.6,0.7,0.8]
X=spline(x,f,5)
S=spline(x,f)
S.coefs
f0=(f(2)-f(1))/(x(2)-x(1))
fn=(f(5)-f(4)/x(5)-x(4))
xx=x([1,3:10,12]);
ff=f([1,3:10,12]);
XX=spline(x,[f0,f,fn],5)
SS=spline(x,[f0,f,fn])
S.coefs