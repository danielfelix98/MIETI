recObj = audiorecorder;
disp('Start speaking.')
recordblocking(recObj, 5);
disp('End of Recording.');
%play(recObj);
y = getaudiodata(recObj);

plot(y);

fsamp = 8000;
fcuts = [fsamp/4 1.2*fsamp/4]; %limites da banda de transicao
mags = [1 0];
devs = [0.01 0.001];

for i = 1:5
    [n,Wn,beta,ftype] = kaiserord( fcuts/i, mags, devs, fsamp);

    hd =  fir1(n,Wn,ftype,kaiser(n+1,beta),'noscale');

    figure(8)
    f_original = filter(hd,1,y);
    
    f_compact = downsample(f_original, i); 
    
    freqz(hd);

    disp('N=');
    disp(i);
    figure(3)
    plot(y,'r')
    hold on
    plot(f_compact,'g')
    title('Sinais original e filtrado no tempo')
    legend('Original','Filtrado');
    hplayer = audioplayer(f_compact, 8000);
    play(hplayer);
    pause(5); % esperar pelo fim do som gravado
end