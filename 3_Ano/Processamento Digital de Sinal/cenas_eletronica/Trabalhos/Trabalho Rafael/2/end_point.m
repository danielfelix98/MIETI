function [noise, clean, SNR] = end_point(x, wlen,fr, thresh, db_white_noise)

m=mean(x(1:length(x)));		%calcular a media
v=var(x(1:length(x)));		%calcular a variancia	

alfa=fr*wlen;               %calcular o threshold
clean=0;				    %buffer para a fala
noise=0;			        %buffer para o ruido
buffer_classifica = 1:1:length(x);	         %buffer para as validacoes

if(rem(wlen,2)==1)          %ver se a janela e par senao � adicionar 1 ao tamanho da janela
     wlen=wlen+1;
end

% Sinal com ruido branco adicionado
asnr = awgn(x,db_white_noise,'measured');
figure(2);
plot(asnr,'color','b')

% o ciclo seguinte e para ver se cada posiçao do sinal amostrado  e fala
% ou ruido se o modulo da soma dessa posiçao com media for maior que o desvio padrao 
% e fala logo o  buffer de validdacao ficara com valor 1 nessa posicao senao e ruido e ficara com o valor 0

for i=1: length(asnr)			 
    if(abs(asnr(i)-m)>(thresh*sqrt(v)))	 	
        buffer_classifica(i)=1;
    else				
        buffer_classifica(i)=0;
    end
end

 %iniciar a janela na posicao 1 até ao tamanho dado pelo argumento de entrada wlen

initw=1;
endw=initw+wlen;
prev_noise=0;  %inicializar a variavel correspondente ao estado anterior(se ruido ou se fala) a 0

while(endw<length(x))
    w=buffer_classifica(initw:endw);                %copiar os dados do buffer de validacao correspondente a janela atual para um buffer auxiliar

    if(sum(w)>alfa)                                 %caso o somatorio dos valores do buffer auxiliar seja maior que o threshold colocar os dados correspondentes ao buffer do sinal no buffer de fala
        if(prev_noise==1)	
            clean=cat(1, clean, x(initw:endw));     %caso o somatorio dos valores do buffer auxiliar seja maior que o threshold colocar os dados correspondentes ao buffer
                                                    % do sinal no buffer de fala
        else			
            clean=cat(1, clean, x(initw+wlen/2:endw));  % caso a janela anterior tenha sido no buffer de fala colocar neste buffer
                                                        % coloca os dados correspondentes so à ultima metade da janela
        end                                             %atualiza a variavel estado anterior para o estado atual
        prev_noise = 0;
    else			
        if(prev_noise==1)	
            noise=cat(1, noise, x(initw+wlen/2:endw));

        else			
            noise=cat(1, noise, x(initw:endw));

        end
        prev_noise = 1;
    end

    initw=initw+wlen/2;  %define a proxima janela 
    endw=endw+wlen/2;

    if(endw>length(x))	   % condicão caso o numero de janelas nºao de um numero inteiro 
        endw=length(x);
        initw=endw-initw;  
    end
end

clean_mean=mean(clean.^2);    % calcular a media do buffer de fala
noise_mean=mean(noise.^2);    % calcular a media do buffer de ruido
SNR=20*log(clean_mean/noise_mean)    %calcular o SNR
