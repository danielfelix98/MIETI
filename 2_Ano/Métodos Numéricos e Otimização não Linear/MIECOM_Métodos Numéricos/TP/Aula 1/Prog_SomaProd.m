clear all
n=input('quantos termos?: ');
for i=1:n
    x(i)=input(['introduza o ', num2str(i), 'ºnúmero ']);
end
[a,b]=SomaProd(x);
disp('A soma é: ');disp(a);
disp('O produto é: ');disp(b);
