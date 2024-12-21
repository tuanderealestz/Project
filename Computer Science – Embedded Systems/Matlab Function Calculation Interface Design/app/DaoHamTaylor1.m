function [ydh] = DaoHamTaylor1(x,fx,h,pp)
%UNTITLED Summary of this function goes here
%   Detailed explanation goes here
if pp == "tien"
    ydh = ((fx(x+h) - fx(x))/h);
elseif pp == "lui"
    ydh = ((fx(x) - fx(x-h))/h);
end

