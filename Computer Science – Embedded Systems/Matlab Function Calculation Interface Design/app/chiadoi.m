function [c,n] = chiadoi(fx,a,b,saiso)
%UNTITLED2 Summary of this function goes here
%   Detailed explanation goes here
fx = str2func(['@(x)',fx]);
n =0;
    while(1)    
        c = (a+b)/2;
        if(fx(c)*fx(a)<0)
            b = c;
        else
            a = c;
        end
        e = b-a;
        n = n + 1;
        if(e < saiso)
            break;
        end
    end
end

