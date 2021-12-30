% gravacao= audiorecorder;
% disp('Start speaking.')
% recordblocking(gravacao,4);
% disp('End of Recording.');
%  play(gravacao); %ouvir se a gravação ficou bem gravada
% y = getaudiodata(gravacao);%armazenar dados num array
%  audiowrite('som.wav',y,8000);

%como o audio foi ja escrito com fs=8000 ao ser lido é lido com essa mesma
%frequencia

[y,fs]=audioread('som.wav');
figure(1)
subplot(2,1,1)
plot (y) %ver gráfico
title('Sinal Original');
% play(gravacao);
% % 
% % 



rp=40;            %ripple na banda passante
rs=60;            %ripple na banda de rejeição
N=3;
wp=pi/N;          %frequencia de corte
ws=wp+(0.2*wp);   %frequencia de banda
%Nd=2;             %frequencia de sub-amostragem

% 
Nd=5;
[n,Wn] = buttord((2*fs*tan(wp/2))/Nd,(2*fs*tan(ws/2))/Nd,rp,rs,'s');


[b,a]=butter(n,Wn,'s');


[bd,ad]=bilinear(b,a,fs);
figure(2)
freqz(bd,ad);
sinalFiltrado=filter(bd,ad,y);
figure(3)
subplot(2,1,1)
plot(sinalFiltrado)
title('sinal aplicação do filtro');
sinal_downsample=downsample(sinalFiltrado,Nd);



player = audioplayer(sinal_downsample, fs);
disp('Start playing');
play(player);
disp('End of playing');
figure(4)
subplot(2,1,1)
plot(sinal_downsample)



title('sinal apos downsample');
