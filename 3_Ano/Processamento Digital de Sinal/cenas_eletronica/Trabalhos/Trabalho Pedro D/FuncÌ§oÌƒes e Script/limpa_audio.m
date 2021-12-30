function [] = limpa_audio( audio )

% 1º - Determinar SNR (ver 0.6seg do audio para ruído);
% 2º - Determinar qual alpha devo usar;
% 3º - Aplicar algoritmo com threshold e alpha decidido em cima.

% Seleçao da parte de sinal (0.6 segundo)
ruido = audio(1:round(0.6/(1/44100)));
media_ruido = mean(ruido);
variancia_ruido = std(ruido);
r=((std(ruido))^2)+((mean(ruido))^2);%potência de ruido

sumatorio=0;
for(i=1:length(audio))
    sumatorio=sumatorio+audio(i).^2;
end
s=sqrt((1/(length(audio)))*sumatorio); %media quadratica do sinal

SNR=10*log10(((s-r)/r));
SNR=SNR-2.5;
alpha =0;
aux=0;

if SNR <8
    disp('impossível recuperar sinal');
else
    if SNR >=8 && SNR <10
        alpha = 1.8;
    else
        if SNR >=10 && SNR <12
            alpha = 1.9;
        else
            if SNR >=12 && SNR <14
                alpha = 2;
            else
                if SNR >=14 && SNR <16
                    alpha = 2.2;
                else
                    if SNR >=16 && SNR <18
                        alpha = 2.3;
                    else
                        if SNR >=18 && SNR <22
                            alpha = 2.45;
                        end
                    end
                end
            end
        end
    end
end

disp('SNR detetado =');disp(SNR);
disp('alpha a utilizar =');disp(alpha);

threshold = media_ruido + alpha * variancia_ruido; %threshold para
threshold_acima = 0;
threshold_abaixo = 0;
tam_janela=30;
fala = [];
ruidoapa = [];

for i=1:30:length(audio)
    if length(audio)-i<29
        aux=length(audio)-i;
    else aux = 29;
    end
    for j=i:1:i+aux
        if(abs(audio(j)) > abs(threshold))
            threshold_acima = threshold_acima + 1;
        else
            threshold_abaixo = threshold_abaixo + 1;
        end
    end
    if(threshold_acima >= 0.15*tam_janela) %guardo a fala
        fala = [fala; audio(i:i+aux)];
    else
        ruidoapa = [fala; audio(i:i+aux)]; %útil para debug
    end
    threshold_acima = 0;
    threshold_abaixo = 0;
end

figure(4);
plot(fala);
title('INFORMACAO');
xlabel('n');
ylabel('AMPLITUDE');

pause(3);
disp('A ouvir sinal recuperado...')
sound(fala, 44100, 16);

end

