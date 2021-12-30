clear all;
clc;
x=[1,1.5,2,3,3.5];
f=[0,0.4055,0.6931,1.0986,1.2528];
X=spline(x,f,2.5)
S=spline(x,f)
S.coefs
f0=1/x(1);
fn=1/x(5);
XX=spline(x,[f0,f,fn],2.5)
SS=spline(x,[f0,f,fn])
S.coefs


