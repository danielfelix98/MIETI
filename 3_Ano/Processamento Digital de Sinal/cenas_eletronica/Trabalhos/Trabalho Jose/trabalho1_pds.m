Fs= 8000
% filename = 'nice-work.wav'
filename = 'you.wav'
[array, Fs] = audioread(filename)
sound(array, Fs, 8)
pause (2)



% [N, Wp]= cheb1ord (.25, .3, -20*log10(0.01), -20*log10(0.001));
% message = ['N = ', num2str(N)]
% disp(message)
% 
%  [b,a] = cheby1(N,-20*log10(0.01),Wp);

  
%   player = audioplayer(filteredVoice, Fs);
%   play(player);
  
%   for n= 2:8
%       filteredVoice = filter (b,a,unfilteredVoice);
%       
%   end
%   plot (unfilteredVoice)

%   filteredVoice = filter (b,a,unfilteredVoice)
%   
%   ydecimado = downsample(filteredVoice, 6)
%   plot (filteredVoice)
%   hold on
%   plot (ydecimado)
%   %sound (unfilteredVoice)
%   pause(3)
%   sound (filteredVoice)
%   pause(3)
%   sound (ydecimado)


  
  
 