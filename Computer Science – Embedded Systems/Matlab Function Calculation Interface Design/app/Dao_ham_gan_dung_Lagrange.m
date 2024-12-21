function dx = Dao_ham_gan_dung_Lagrange(xa,ya,x1)
%UNTITLED3 Summary of this function goes here
%   Detailed explanation goes here
syms x;
a = Lagrange(xa,ya,x);
b = sym2poly(a);
dx = polyval(polyder(b),x1);
end

