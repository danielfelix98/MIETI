 gravacao = audiorecorder(4000,8,1);   %Criação do Objeto para Gravação
 disp('Inicio da gravacao.')
 recordblocking(gravacao, 2);%Gravação por 2 segundos no Objeto
 disp('Fim da gravacao.')
 play(gravacao);             %Reprodução do Objeto
 pause(3);
signal = getaudiodata(gravacao); %Conversão do Objeto para um Array

% fator = fracção de 1's 
% tamanho_janela = tamanho da janela a analisar    
% numero_amostras = numero de amostras por segundo

tamanho_janela = 130;
fator = 0.6;
numero_amostras = 400;

%definir aqui os valores de dB para o ruído branco
asnr = awgn(signal,0,'measured'); % sinal com ruido branco - 0 dB a 50 dB

%calculo da media
m = mean(asnr(1:numero_amostras));

%calculo da variancia
v = var(asnr(1:numero_amostras));                           

%criação de uma matriz para guardar 
% se amostra é ruído ou fala
aux = 1:1:length(asnr);

%separar sinais de fala e de ruido e guardar posições em aux
for a=1:length(asnr)                          
    if abs(asnr(a,1)-m)>sqrt(v)
        %na posição i, guarda 1 se for fala
        aux(a,1) = 1;                         
    else
        %na posição i, guarda 0 se for ruído
        aux(a,1) = 0;                               
    end
end

% inicialização dos buffers
buffer_ruido = 0;
buffer_fala = 0;
%fator de definição se é uma sequência de fala(com tantos 1's é fala)
alpha = tamanho_janela * fator; 
%define o inicio da janela   
inicio_janela = 1;
fim_janela = tamanho_janela;


while((fim_janela < length(asnr)))        %se ainda não se chegou ao fim de toda a gravação audio
    
    j = aux(inicio_janela:fim_janela);%armazena a sequência correspondente a uma só janela
    
    if sum(j) > alpha                              %se o número de 1's for superior a alpha -- fala
        if ~buffer_fala                                    %se ainda não houve o array da fala                     
            buffer_fala = asnr(inicio_janela:fim_janela);
        else                                        %une os dois arrays que contêm fala, num só array
            buffer_fala = cat(1,buffer_fala,asnr(inicio_janela:fim_janela));
        end
        
    else                                            %se o número de 1's for inferior a alpha -- ruído
        if ~buffer_ruido                                   %se ainda não houve o array ruido 
           buffer_ruido = asnr(inicio_janela:fim_janela);
        else                                        %une os dois arrays que contêm ruído, num só array
           buffer_ruido = cat(1,buffer_ruido,asnr(inicio_janela:fim_janela));
        end
    end

    inicio_janela = fim_janela;
    fim_janela = fim_janela + tamanho_janela;
end

snr = 20*log(mean(buffer_fala)/sqrt(var(buffer_ruido)));

figure(1);
subplot(3,1,1) 
plot(signal,'color','b') 
title('Sinal original','Color','b');
subplot(3,1,2)
plot(buffer_ruido,'Color','b') 
title('Ruido','Color','b');
subplot(3,1,3)
plot(buffer_fala,'Color','g')
title('Fala','Color','g');