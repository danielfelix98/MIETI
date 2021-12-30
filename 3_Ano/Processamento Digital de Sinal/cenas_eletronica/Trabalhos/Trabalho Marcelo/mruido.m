function [noisebuff, buff] = mruido(x, nseg, wlen, fr)

m=mean(x(1:nseg));
v=var(x(1:nseg));

alfa=fr*wlen;
buff=0;
noisebuff=0;
a = 1:1:length(x);


if(rem(wlen,2)==1)
     wlen=wlen+1;
end

for i=1: length(x)
    if(abs(x(i)-m)>sqrt(v))
        a(i)=1;
    else
        a(i)=0;
    end
end

initw=1;
endw=initw+wlen;
prev_noise=0;


        
while(endw<length(x))
    w=a(initw:endw);
    if(sum(w)>alfa)
        if(prev_noise==1)
            buff=cat(1, buff, x(initw:endw));
        else
            buff=cat(1, buff, x(initw+wlen/2:endw));
        end
    else
        if(prev_noise==1)
            noisebuff=cat(1, noisebuff, x(initw+wlen/2:endw));
        else
            noisebuff=cat(1, noisebuff, x(initw:endw));
        end
    end
    
    initw=initw+wlen/2;
    endw=endw+wlen/2;
    
    if(endw>length(x))
        endw=length(x);
        initw=endw-initw;
    end
end


subplot(3,1,1), plot(x);
subplot(3,1,2), plot(buff);
subplot(3,1,3), plot(noisebuff);