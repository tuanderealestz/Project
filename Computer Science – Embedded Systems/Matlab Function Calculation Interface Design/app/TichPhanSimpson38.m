function y = TichPhanSimpson38(fx,a,b,n)
%UNTITLED2 Summary of this function goes here
%   Detailed explanation goes here
h = (b-a)/n;
sum1 = 0;
sum2 = 0;
sum3 = 0;
y = fx(a) + fx(b);
for i = 1:3:n-2
    sum1 = sum1 + fx(a + i*h);
end
for i = 2:3:n-1
    sum2 = sum2 + fx(a + i*h);
end
for i = 3:3:n-3
    sum3 = sum3 + fx(a + i*h);
end
y = (3*h/8)*(y + 3*sum1 + 3*sum2 + 2*sum3);
disp(['Ket qua tich phan = ',num2str(y)]);
end

