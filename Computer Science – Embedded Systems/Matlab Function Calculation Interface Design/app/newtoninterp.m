function [v, d] = newtoninterp(x, y)
%input: x,y output: v la da thuc chua rut gon
    if nargin<3
        u=sym('x');
    end
    n=length(y);
    if length(x) ~= n
        error('x and y are not compatible!');
    end
    d = y(:);
    for j = 2:n
        for i = n:-1:j
            d(i) = (d(i)-d(i-1))/(x(i)-x(i-j+1));
        end
    end
    v = d(n)* ones(size(u));
    for i = n-1:-1:1
        v = v.*(u-x(i))+d(i);
    end
end