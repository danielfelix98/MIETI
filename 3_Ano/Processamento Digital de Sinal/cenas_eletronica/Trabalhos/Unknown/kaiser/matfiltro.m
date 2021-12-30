% Parametros para inserir no kaiserord
Sampling_Frequency = 8000; % frequencia de amostragem
rp=40;
rs=60;
N=2;

recording = audiorecorder(Sampling_Frequency,8,1); %cria objeto da gravação
disp('Inicio da gravacao.')
recordblocking(recording, 5);%inicia a gravação por 5s
disp('Fim da gravacao.');
recorded_audio = getaudiodata(recording);
plot(recorded_audio,'r')


[n,Wn,beta,ftype] = kaiserord(fcuts,mags,devs,fsamp);
filtro = fir1(n,Wn,ftype,kaiser(n+1,beta));
figure (1);
title ('Filtro a ser utilizado');
freqz(filtro);

filtered_audio = filter(filtro,1,recorded_audio);
figure(2)

hold on
plot(filtered_audio, 'g')
title('Sinais original e filtrado no tempo');
legend('Original','Filtrado');

filtered_audio = downsample(filtered_audio,Nd);


hplayer = audioplayer(filtered_audio*5, Sampling_Frequency);
play(hplayer);


