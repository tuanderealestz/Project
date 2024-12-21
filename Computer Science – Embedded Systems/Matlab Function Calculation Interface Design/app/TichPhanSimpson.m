function y = TichPhanSimpson(fx,a,b,n)
%UNTITLED2 Summary of this function goes here
%   Detailed explanation goes here
h = (b-a)/n;
sumle = 0;
sumchan = 0;
y = fx(a) + fx(b);
for i = 1:2:n-1
    sumle = sumle + fx(a + i*h);
end
for i = 2:2:n-1
    sumchan = sumchan + fx(a + i*h);
end
y = (h/3)*(y + 4*sumle + 2*sumchan);
disp(['Ket qua tich phan = ',num2str(y)]);
end

