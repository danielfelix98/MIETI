
        function [noise, clean, SNR] = noise_elimination(x, wlen,fr)

    m=mean(x(1:length(x)));		
    v=var(x(1:length(x)));			
     
    alfa=fr*wlen;
    clean=0;				
    noise=0;			
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
                clean=cat(1, clean, x(initw:endw));
            else			
                clean=cat(1, clean, x(initw+wlen/2:endw));
            end
            prev_noise = 0;
        else			
            if(prev_noise==1)	
                noise=cat(1, noise, x(initw+wlen/2:endw));
            else			
                noise=cat(1, noise, x(initw:endw));
            end
            prev_noise = 1;
        end
        
        initw=initw+wlen/2;
        endw=endw+wlen/2;
        
        if(endw>length(x))	    
            endw=length(x);
            initw=endw-initw;
        end
    end
     
    %subplot(3,1,1), plot(x);
    %subplot(3,1,2), plot(c);
    %subplot(3,1,3), plot(noise);

    clean_mean=mean(clean.^2);
    noise_mean=mean(noise.^2);
    SNR=20*log(clean_mean/noise_mean)
