
time_talk = 3
minor_time_talk = 2
record = audiorecorder            %fsample é 8kHz por defeito
message1 = ['Start speaking, you have ', num2str(time_talk), ' seconds']
disp(message1)
recordblocking(record, time_talk)
f = getaudiodata(record);
disp('End of Recording.')           
sound(f)


%  filename = 'som8.wav'
%  [y, Fs] = audioread(filename)
%  sound(y, Fs)
 

fs = 8000                   %frequencia de amostragem
fcut = [1000 1200]          %banda passante e banda de rejeição
ripple = [0.01 0.001]       %ripple: 40dB na banda passante e 60dB na banda de rejeição
amp_band = [1 0]            %amplitude de banda

[n,Wn,beta,ftype] = kaiserord(fcut,amp_band,ripple,fs)
message = ['n = ', num2str(n) , '     beta = ', num2str(beta) ]
disp(message)
disp(ftype)     %lowpass

 b = fir1(n,Wn,ftype,kaiser(n+1,beta))
  wvtool(b)
  figure(3)
  freqz(b,1,1024,fs)
  figure(4)
  
  
c = filter(b,2,f)       %f%y
plot(f)
hold on
plot(c)
hold on
pause(time_talk)
sound(c)
pause(time_talk)


for fn=2:4
d = downsample(c,fn)
plot(d)
sound(d)
pause(time_talk)

end

