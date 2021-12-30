function [fala,ruido] = detetor_fala(fich_audio, noise_len, pause_len, espor_noise_len)
% detetor_fala -> função que analisa o sinal de áudio e separa o ruido da
% fala através da criação de 2 vetores 
 
% Argumentos de entrada:
%   fich_audio: vetor com o sinal áudio a analisar
%   noise_len: número de amostras inicias onde se grava ruido 
%   pause_len: duração do tempo de pausa permitido no segmento de
%   voz(amostras), normalmente 50
%   espor_noise_len: número máximo de amostras que um ruido esporádico pode tomar
 
% Argumentos de saída:
%   ruido: vetor que guarda o segmento de ruido (ruido removido)  
%   fala: vetor que guarda o segmento de fala sem ruido
 
    %Inicializações
    ruido=0;            %vetor segmento de ruido inicializado a 0    
    fala=0;             %vetor segmento de fala inicializado a 0 
    
    con_espor=0;        %variável contador do número de amostras para saber se o sinal obtido é esporádico ou não
    con_pausa=0;        %variável contador do número de amostras para saber se o sinal obtido é uma pausa entre as falas ou não
    n_amostras=0;       %variável auxiliar contador do número de amostras
    
    SNR=(mean(fich_audio))/(std(fich_audio));   %SNR=media/desvio_padrao
    
    threshold=SNR*10;                           %threshold calcula um limite, que indica 
    if abs(threshold) < 1                       %qual é a probalidade de encontrar ruido ou fala
        threshold=2;
    end
    
    media=mean(fich_audio(1:noise_len));    %calculo da média 
    dp=std(fich_audio(1:noise_len));        %calculo do desvio-padrão do ruido inicial
    
    %Algoritmo da função
    for i=1:length(fich_audio)                                                      %percorre-se o ficheiro de áudio e compara-se
        if abs(fich_audio(i)) > (media + abs(threshold)*dp)                         %se o valor do sinal é maior ao limite calculado é um segmento de fala 
           con_espor = con_espor+1;
           n_amostras = n_amostras+1;
           con_pausa=0;
           if(con_espor) > espor_noise_len                              %se o contador de amostras de ruido esporadico for maior que o valor recebido por parâmetro
               fala=cat(1,fala,fich_audio(i-n_amostras+1:i));            %conta-se como um segmento de fala, senão é removido
               n_amostras=0;
           end 
        else                                                                        %senão é um segmento de ruido
            con_pausa=con_pausa+1;
            n_amostras = n_amostras+1;
            if con_pausa > pause_len                                    %se o contador da pausa for maior que o valor recebido por parametro assume-se que é ruido 
                ruido=cat(1,ruido,fich_audio(i-n_amostras+1:i));
                con_espor=0;
                n_amostras=0;
                con_pausa=0;
            end
        end
    end   
end



