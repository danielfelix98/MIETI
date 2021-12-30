%Definicao do THRESHOLD
THRESHOLD = 0.6;

%---------------------Capturar o som-------------------------

%Definir a frequencia
Fs = 11025;
% Gravar a voz por 5 segundos
gravarObj = audiorecorder(Fs, 16, 1);
disp('Diga o seu nome')
recordblocking(gravarObj, 5);

% Guardar dados
disp('A guardar gravação...');
myRecording = getaudiodata(gravarObj);

% Plot da gravacao.
figure; subplot(3,1,1); plot(myRecording,'color','b') 
title('Sinal original','Color','b');
%Gravar, em ficheiro

wavwrite(myRecording,Fs,8,'C:\Users\windows\Desktop\UM\PDS\PDS final\pedro.wav');
disp('Gravação guardada em ficheiro');


%---------------ler o som a partir do ficheiro------------------

y = wavread('C:\Users\windows\Desktop\UM\PDS\PDS final\pedro.wav');
 
samplePerFrame=floor(Fs/100);
bgSampleCount=floor(Fs/5);



soma=0;
for i=1:1:length (y);
	soma=soma + y(i)^2;
end

z=mean(soma);

n=randn (1,length(y));

x=sqrt(z/100000);


N=x*n;

Y=y+N';
 
%------------Calculo da media e do desvio padrao-----------------
bgSample=[];
for i=1:1:bgSampleCount
    bgSample=[bgSample Y(i)];
end
meanVal=mean(bgSample);
sDev=std(bgSample);
 
 
 
%Identificar, para cada valor, se ha voz ou nao
for i=1:1:length(Y)
   if(abs(Y(i)-meanVal)/sDev > THRESHOLD)
       voiced(i)=1;
   else
       voiced(i)=0;
   end
end
 
 
%identificar se ha voz ou nao para cada frame
 
%rejeitar as samples insuficientes da ultima frame
 
usefulSamples=length(Y)-mod(length(Y),samplePerFrame);
frameCount=usefulSamples/samplePerFrame;
voicedFrameCount=0;
ruidoCont=0;
for i=1:1:frameCount
   cVoiced=0;
   cUnVoiced=0;
   for j=i*samplePerFrame-samplePerFrame+1:1:(i*samplePerFrame)
       if(voiced(j)==1)
           cVoiced=(cVoiced+1);
       else
           cUnVoiced=cUnVoiced+1;
       end
   end
   
   %marcar as frames voz ou nao-voz 
   if(cVoiced>cUnVoiced)
       voicedFrameCount=voicedFrameCount+1;
       voicedUnvoiced(i)=1;
   else
       voicedUnvoiced(i)=0;
       ruidoCont=ruidoCont+1;
   end
end


 
sinalFinal=[];
 
%-----
for i=1:1:frameCount
    if(voicedUnvoiced(i)==1)
    for j=i*samplePerFrame-samplePerFrame+1:1:(i*samplePerFrame)
            sinalFinal= [sinalFinal Y(j)];
        end
    end
end
%------------------
ruido=[];

for i=1:1:frameCount
    if(voicedUnvoiced(i)==0)
    for j=i*samplePerFrame-samplePerFrame+1:1:(i*samplePerFrame)
            ruido= [ruido Y(j)];
        end
    end
end

%------ mostrar os graficos do sinal original e do sinal sem silencios
    subplot(3,1,2), plot(y,'Color','b') 
    title('Antes de aplicada a Remocao de Silencios','Color','b');
 
    subplot(3,1,3), plot(sinalFinal,'Color','g')
    title('Depois de aplicada a Remocao de Silencios','Color','g');
    
 
%----------------play dos dois sinais------------------------------
%sound(y,Fs);
%sound(ruido,Fs);
%sound(sinalFinal,Fs);