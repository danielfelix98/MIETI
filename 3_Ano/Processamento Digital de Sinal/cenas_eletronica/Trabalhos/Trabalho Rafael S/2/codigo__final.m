%frequencia de amostragem
Fs=8000;

%Criação do Som
gravacao=audiorecorder; %criar o Objecto
disp('Inicio da Gravaçao.') 
recordblocking(gravacao,5); %gravação do audio por 5 segundos
disp('Fim da Gravação.')
play(gravacao); %reprodução do Objecto(gravação)
y=getaudiodata(gravacao); %conversão do Objecto da gravação para um Array
audiowrite('som.wav',y,8000); %escrita de um ficheiro .wav com o Array
[y,Fs]=audioread('som.wav'); %leitura do ficheiro .wav



%Informaçoes do som 
info=audioinfo('som.wav');
disp(info);
[y,Fs]=audioread('som.wav'); %leitura do ficheiro .wav

tamanho_janela = 150;                   %tamanho da janela a analisar  
fator = 0.5;                            %fracção de 1s
numero_amostras = 8000;
n_seg = 8000;                           %numero de amostras por segundo


asnr = awgn(y,20,'measured');       % atribuição dos valores db do ruido branco de 0dB-40dB

media = mean(asnr(1:n_seg));            %calculo da media
variancia = var(asnr(1:n_seg));         %calculo da variancia                  
buffer_ruido = 0;                       % iniciar buffer ruido
buffer_fala = 0;                        % iniciar buffer fala
aux = 1:1:length(asnr);                 %cria matriz que guarda se é ruido ou fala
alpha = tamanho_janela * fator;         %fator de definição para verificar se é uma seq. de fala(com tantos 1's é fala)

for a=1:length(asnr)                    %separa os sinais da fala, do ruido e guarda posições em aux                         
    if abs(asnr(a)-media)>sqrt(variancia)
        aux(a) = 1;                   %se for fala fica a 1 na posicao i                        
    else
        aux(a) = 0;                   %se for ruido fica a 0 na posicao i                             
    end
end




   
inicio_janela = 1;                      %define o inicio da janela
fim_janela = tamanho_janela;

while((fim_janela < length(asnr)))       %caso não tenha chegado ao fim de toda a gravação audio
    
    j = aux(inicio_janela:fim_janela);   %guarda a seq. correspondente a uma janela
    
    if sum(j) > alpha                    %caso número de 1 for maio que a alpha - fala
        if ~buffer_fala                  %se ainda não houver o array da fala                     
            buffer_fala = asnr(inicio_janela:fim_janela);
        else                             %une os dois arrays que contêm fala num só
            buffer_fala = cat(1,buffer_fala,asnr(inicio_janela:fim_janela));
        end
        
    else                                  %caso número de 1 for menor a alpha - ruído
        if ~buffer_ruido                  %se ainda não houve o array ruido 
           buffer_ruido = asnr(inicio_janela:fim_janela);
        else                              %une os dois arrays que contêm ruído num só
           buffer_ruido = cat(1,buffer_ruido,asnr(inicio_janela:fim_janela));
        end
    end

    inicio_janela = fim_janela;
    fim_janela = fim_janela + tamanho_janela;
end

snr = 10*log(mean(buffer_fala.^2)/mean(buffer_ruido(1:(Fs/5)).^2)); %calculo do SNR

figure(1);
subplot(3,1,1) 
plot(y,'color','b') 
title('Sinal original','Color','b');
subplot(3,1,2)
plot(buffer_ruido,'Color','b') 
title('Ruido','Color','b');
subplot(3,1,3)
plot(buffer_fala,'Color','g')
title('Fala','Color','g');
