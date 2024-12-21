function v=lagrangeinterp(x,y,u)
%input: x,y output: v la da thuc chua rut gon
    if nargin<3
        u=sym('x');
    end
    n=length(x);
    v=zeros(size(u));
    for i=1:n
        w=ones(size(u));
        for j = [1:i-1 i+1:n]
            w = (u-x(j))./(x(i)-x(j)).*w;
        end
        v = v + w*y(i);
    end
end