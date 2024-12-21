function y = TichPhanHinhThang(f,a,b,n)
%UNTITLED Summary of this function goes here
%   Detailed explanation goes here
h = (b-a)/n;
y = f(a) + f(b);
sum = 0;
for i=1:n-1
    x_i = a+i*h;
    sum = sum +f(x_i);
end
y = (h/2)*(y + 2*sum);
disp(['Ket qua tich phan = ',num2str(y)]);
end

