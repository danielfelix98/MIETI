gravacao = audiorecorder (8000,8,1); % 8000 Hz, 8-bit, 1-channel
disp('Inicio da gravacao.')
recordblocking(gravacao, 3);
disp('Fim da gravacao.');
audio_gravado = getaudiodata(gravacao);
figure (1);
plot (audio_gravado);
title ('Sinal Original');


% Parametros para inserir no kaiserord
Sampling_Frequency = 8000; % frequencia de amostragem
Limites_Banda_transicao=[Sampling_Frequency/4 1.2*Sampling_Frequency/4]; % 20% banda passante
mags = [1 0]; % Filtro Passa Baixo
devs = [0.01 0.001]; % Ripple passa banda e atenuação na banda de rejeicao


for i=1:5
[n,Wn,beta,ftype] = kaiserord(Limites_Banda_transicao/i ,mags ,devs ,Sampling_Frequency);
filtro = fir1(n,Wn,ftype,kaiser(n+1,beta),'noscale');

figure (2);
audio_filtrado = filter(filtro,1,audio_gravado);

audio_compactado = downsample(audio_filtrado, i);
freqz (filtro);

disp('N=');
    disp(i);
    figure(3)
    plot(audio_gravado,'r')
    hold on
    plot(audio_compactado,'g')
    title('Sinais original e filtrado no tempo')
    legend('Original','Filtrado');
    hplayer = audioplayer(audio_compactado, 8000/i);
    play(hplayer);
    pause(5); % esperar pelo fim do som gravado
end
