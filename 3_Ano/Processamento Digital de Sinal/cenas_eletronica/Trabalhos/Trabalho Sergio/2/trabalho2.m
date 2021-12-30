
%%%%%%VARIÁVEIS DE ENTRADA
    time_talk = 5
    fs = 8000                                                              
    nbits = 16                                                             
    nchannels = 1                                                        
    Length = 7;
    audio_file = 'C:\Users\sergi\OneDrive\Ambiente de Trabalho\Universidade\PDS\som8k.wav'
    SNR = 50      
    threshold = 0;
    fraction_of_ones = 0.35;
    index_jump = 1400;
    size_of_window = 1500;
    
 %%%%%%%%%%%%%%%%
 
 
%%%%%%GRAVAÇÃO DO SINAL ÁUDIO 

record = audiorecorder(fs,nbits, nchannels)     %objeto para a gravação de áudio       
message1 = ['Start speaking, you have ', num2str(time_talk), ' seconds']
disp(message1)
recordblocking(record, time_talk)       %grava o áudio durante 'time_talk' segundos
f = getaudiodata(record)
disp('End of Recording.')
audiowrite(audio_file,f,fs)     %escrita dos dados da gravação num ficheiro .wav

plot(f)
figure(2)



%  filename = 'som8k.wav'
%  [f, fs] = audioread(filename)
 


%%%%%%%%%%%%%%%%

%%%A contaminar o ruido%%%
disp('A contaminar o sinal com o SNR desejado...')
    f_energy = power(f,2)             %cálculo da energia do sinal de áudio
    f_energy = mean(f_energy)             %cálculo da energia do sinal de áudio
    wn = randn(1,length(f))              %sinal de ruído do tamanho do sinal de áudio A
    wn = wn - mean(wn)                           %média 0
    wn = wn * sqrt(f_energy / (10^(SNR / 10)))                                
    contaminated = f + wn'                                                           
   
    plot(contaminated)
    figure(3)
    
 %%%a detetar as pausas%%%   
 disp('A eliminar todas as pausas...');
    if (SNR > 0 && SNR < 15) threshold = 0.45;
    elseif (SNR > 15 && SNR < 25) threshold = 0.5;      %o valor do treshold varia consoante o SNR escolhido
    elseif (SNR > 25 && SNR < 35) threshold = 0.6;
    elseif (SNR > 35 && SNR < 45) threshold = 0.75;
    else threshold = 0.8;
    end
    ruido = 0;
    fala = 0;
    cont_mean = mean(contaminated);        %cálculo da média do sinal 
    cont_desv = std(contaminated);         %cálculo do desvio padrão do sinal de áudio
    cont_array = 1:1:length(contaminated);     %array com o tamanho do sinal áudio onde são guardados os zeros e uns
    for i=1:length(contaminated)       %percorrer o sinal de áudio e colocar zeros e uns em cont_array
        if(abs(contaminated(i) - cont_mean) / cont_desv > threshold)               %se é um outlier (fala)
            cont_array(i) = 1;                                                      %coloca 1 no array
        else                                                                %se é ruído
            cont_array(i) = 0;                                                      %coloca 0 no array
        end
    end
    n_ones = size_of_window * fraction_of_ones;              %quantidade de 1's para ser validado como fala
    n = 1;
    while(((n-1)*index_jump + size_of_window) < length(contaminated))                %se a gravação ainda não acabou
        j = cont_array((n-1)*index_jump + 1 : (n-1)*index_jump + size_of_window);   %armazena a informação de 1 janela
        if sum(j) > n_ones                                                  %se for fala
            if ~fala                                                        %se o buffer da fala for nulo
                fala = contaminated((n-1)*index_jump + 1 : (n-1)*index_jump + size_of_window);
            else                                                            %concatena os buffers que contêm fala
               fala = cat(1,fala,contaminated((n-1)*index_jump + 1 : (n-1)*index_jump + size_of_window));
            end
        else                                                                %se for ruído
            if ~ruido                                                       %se o buffer do ruido for nulo
                ruido = contaminated((n-1)*index_jump + 1 : (n-1)*index_jump + size_of_window);
            else                                                            %concatena os buffers que contêm ruído
                ruido = cat(1,ruido,contaminated((n-1)*index_jump + 1 : (n-1)*index_jump + size_of_window));
            end
        end
        n=n+1;                         
    end
    
     subplot(3,1,1), plot(f,'Color','g')
     title('Sinal áudio a analisar','Color','g')
    subplot(3,1,2), plot(contaminated,'Color','r')                                     
    title('Sinal contaminado','Color','r');
    subplot(3,1,3), plot(fala,'Color','b')
    title('Sinal com intervalos de silêncio removidos','Color','b');
     sound(f)
     pause(5);
     sound(contaminated)
     pause(5);
    sound(fala);
    pause(5);


