function [speechbuf, noisebuf, nmean, nvar, ndev, snr] = sigproc (audiocap, noiselen, windlen, alfa)
    auxarr = zeros(size(audiocap,1),1);
    nmean = mean(audiocap(1:noiselen));
    nvar = var(audiocap(1:noiselen));
    ndev = sqrt(nvar);
    
    for i=1:length(audiocap)
        if abs(audiocap(i,1)-nmean) > ndev
            auxarr(i,1) = 1;
        else
            auxarr(i,1) = 0;
        end
    end
    
    begw = 1;
    endw = windlen;
    processing = 1;
    noisebuf=0;
    speechbuf=0;
    final = 0;
    while processing
           if final == 1
            processing = 0;
        end
        tempacap = auxarr(begw:endw,1);
        if sum(tempacap) > alfa*(endw-begw)
            speechbuf = cat(1,speechbuf, audiocap(begw:endw,1));
        else
            noisebuf= cat(1,noisebuf, audiocap(begw:endw,1));
        end
        if begw+windlen < length(audiocap)
            begw=endw;
        end
     
        if endw+windlen < length(audiocap)
            endw=endw+windlen;
        else
            endw=length(audiocap);
            final=1;
        end
        
    end
  snr = 20*log(mean(speechbuf)/sqrt(var(noisebuf)));
end

