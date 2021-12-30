
recording = audiorecorder; %cria o objeto da gravação
disp('Inicio da gravacao.') 
recordblocking(recording, 5);%gravação do audio por 5 segundos
disp('Fim da gravacao.');
recorded_audio = getaudiodata(recording); %conversão do objeto da gravação para um array
plot(recorded_audio);


Sampling_Frequency = 8000; %frequência de amostragem
Cutting_Frequency = [Sampling_Frequency/4 1.2*Sampling_Frequency/4]; %valores da banda de transição
mags = [1 0]; %filtro passa-baixo
devs = [0.01 0.001]; 

for i = 1:5
    [n,Wn,beta,ftype] = kaiserord( Cutting_Frequency/i, mags, devs, Sampling_Frequency);

    filtro =  fir1(n,Wn,ftype,kaiser(n+1,beta),'noscale');

    figure(2)
    filtered_audio = filter(filtro,1,recorded_audio);
    
    filtered_compact = downsample(filtered_audio, i); 
    
    freqz(filtro);
    disp('N:');
    disp(i);
    figure(3)
    plot(recorded_audio,'r')
    hold on
    plot(filtered_compact,'g')
    title('Sinal original e Sinal filtrado')
    legend('Original','Filtrado');
    sinal_player = audioplayer(filtered_compact, 8000);
    play(sinal_player);
    pause(5); 
end