function [] = alpha_pds( audio )

alpha = 1.8 %para já vou descobrindo qual o alpha para recuperar
%daquele SNR

ruido = audio(1:round(0.6/(1/44100)));
figure(2);
plot(ruido);
title('RUIDO de 0.6 segudos do original');
xlabel('n');
ylabel('AMPLITUDE');

media_ruido = mean(ruido); %media
variancia_ruido = std(ruido); %desvio padrao
threshold = media_ruido + alpha * variancia_ruido; %threshold para
%determinar se info ou ruído
threshold_abaixo=0;
threshold_acima=0;
tam_janela = 30;
fala = [];
ruidoapa = [];
j=1;

for i=1:30:length(audio)
    if length(audio)-i<29
        aux=length(audio)-i;
    else aux = 29;
    end
    for j=i:1:i+aux
        if(abs(audio(j)) > abs(threshold))
            threshold_acima = threshold_acima + 1;
            %disp('acima'); %disp(threshold_acima);
        else
            threshold_abaixo = threshold_abaixo + 1;
            %disp('abaixo'); %disp(threshold_abaixo);
        end
    end
    if(threshold_acima >= 0.10*tam_janela) %guardo a fala
        fala = [fala; audio(i:i+aux)];
    else
        ruidoapa = [fala; audio(i:i+aux)]; %caso queira verificar
    end
    threshold_acima = 0;
    threshold_abaixo = 0;
end

pause(2);
figure(4);
plot(fala);
title('INFORMACAO?');
xlabel('n');
ylabel('AMPLITUDE');
pause(5);
disp('A ouvir sinal recuperado...')
sound(fala, 44100, 16);

end

