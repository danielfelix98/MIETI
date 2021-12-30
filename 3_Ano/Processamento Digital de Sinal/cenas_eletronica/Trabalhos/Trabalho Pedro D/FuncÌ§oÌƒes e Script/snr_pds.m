function [ SNR ] = snr_pds( audio )

%Induzir erro no sinal original
fator_ruido = 0.0001 %alterado manualmente para se obter diferentes SNR
sinal_alterado = audio+(randn(length(audio),1).*fator_ruido);


disp('Vai tocar sinal com ruido')
sound(sinal_alterado, 44100, 16);
figure(2);
title('Sinal Alterado');
plot(sinal_alterado);

% Gravação em disco
%wavwrite(sinal_alterado, 44100, 'snr25');

j=1;
sinal=0;

%seleçao da parte de sinal (1 segundo)
ruido = sinal_alterado(1:round(1/(1/44100)));

r=((std(ruido))^2)+((mean(ruido))^2);%potência de ruido

sumatorio=0;
for(i=1:length(audio))
    sumatorio=sumatorio+audio(i).^2;
end
s=sqrt((1/(length(audio)))*sumatorio); %media quadratica do sinal

SNR=10*log10(((s-r)/r))

end

