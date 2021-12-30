% n_seg = nº de amostras do segmento;
% fator = fracção de 1's (outlier de amostras);
% step = avanço na janela;
% janela = tamanho da janela a analisar

function [ruido, fala] = ruido_fala(x, n_seg, fator, step, tam_janela);

m = mean(x(1:n_seg));                               %cálculo da média
v = var(x(1:n_seg));                                %cálculo da variância


a = 1:1:length(x);


for i=1:length(x)                                   %sinal original
    if abs(x(i)-m)>sqrt(v)
        a(i) = 1;                                   % |X - m| > ? (outlier) -- fala
    else
        a(i) = 0;                                   % |X - m| <= ? -- ruido
    end
end


% inicialização dos buffers
ruido = 0;
fala = 0;


alpha = tam_janela * fator;                         %fator de definição se é uma sequência de fala(com tantos 1's é fala)
n = 1;                                              %define o inicio da janela


while(((n-1)*step + tam_janela) < length(x))        %se ainda não se chegou ao fim de toda a gravação audio
    
    j = a((n-1)*step + 1 : (n-1)*step + tam_janela);%armazena a sequência correspondente a uma só janela
    
    if sum(j) > alpha                              %se o número de 1's for superior a alpha -- fala
        if ~fala                                    %se ainda não houve o array da fala                     
            fala = x((n-1)*step + 1 : (n-1)*step + tam_janela);
        else                                        %une os dois arrays que contêm fala, num só array
            fala = cat(1,fala,x((n-1)*step + 1 : (n-1)*step + tam_janela));
        end
        
    else                                            %se o número de 1's for inferior a alpha -- ruído
        if ~ruido                                   %se ainda não houve o array ruido 
           ruido = x((n-1)*step + 1 : (n-1)*step + tam_janela);
        else                                        %une os dois arrays que contêm ruído, num só array
           ruido = cat(1,ruido,x((n-1)*step + 1 : (n-1)*step + tam_janela));
        end
    end

        n=n+1;                                      %incrementa para a posição seguinte
end;

