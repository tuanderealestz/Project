function [x1,n] = tieptuyen(fx,a,b,saiso)
%TIEPTUYEN Summary of this function goes here
%   Detailed explanation goes here
    diff_fx = str2sym(fx);
    diff_fx = diff(diff_fx);
    diff_fx = matlabFunction(diff_fx);
    fx = str2func(['@(x)',fx]);
    n = 0;
    c = (a+b)/2;
    if(fx(a)*fx(c)<0)
        x0 = a;
    else 
        x0 = b;
    end
    while(1)
        x1 = x0-fx(x0)/diff_fx(x0);
        %Cap nhat lan lap
        n = n +1;
        if(abs(x1-x0)< saiso)
            break;
        end
        %Kiem tra
        x0 = x1;
    end
end

