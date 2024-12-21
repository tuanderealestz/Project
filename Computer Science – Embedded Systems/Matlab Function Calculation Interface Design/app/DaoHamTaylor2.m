function [ydh] = DaoHamTaylor2(x,fx,h,pp)
%UNTITLED6 Summary of this function goes here
%   Detailed explanation goes here
if pp == "tien"
    ydh = ((-3)*fx(x) + 4*fx(x + h) -fx(x + 2*h))/(2*h);
elseif pp == "trung tam"
    ydh = (fx(x + h) - fx(x - h))/(2*h);
elseif pp == "lui"
    ydh = (fx(x - 2*h) - 4*fx(x - h) + 3*fx(x))/(2*h);
end
end

