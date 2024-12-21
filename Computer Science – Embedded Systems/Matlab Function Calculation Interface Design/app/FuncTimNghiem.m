function [KQ, n, x] = FuncTimNghiem(fx, fp, a, b, es, pp)
    syms x;
    dfx = matlabFunction(diff(fx,x));
    ddfx = matlabFunction(diff(fx,x,2));

    n=1000;
    test=a:abs(a-b)/n:b;
    for i =1:n/2
        if ddfx(test(i))*ddfx(test(n-i)) <=0
            fprintf('Đạo hàm bậc 2 của fx không đồng điệu trên khoảng phân ly');
            KQ = NaN;
        end
    end

    switch(pp)
        case 'Chia đôi'
            n = 0;
            while (1)
                n = n+1;
                c = (a+b)/2;
                if fx(a)*fx(c) < 0
                    b = c;
                else
                    a = c;
                end
                if abs(b-a) < es
                    KQ = c;
                    break;
                end
            end

        case 'Lặp'
            n = 0;
            c = (a + b)/2;
            if fx(a)*fx(c) < 0
                x0 = a;
            else
                x0 = b;
            end
            while (1)
                n = n + 1;
                x1 = fp(x0);
                if abs(x1-x0) < es
                    KQ = x1;
                    break;
                end
                x0 = x1;
            end

        case 'Newton (Tiếp tuyến)'
            n = 0;
            x0 = a;
            if(fx(x0)*ddfx(x0) < 0)
                x0 = b;
            end
            while(1)
                n = n+1;
                x1 = x0-fx(x0)/dfx(x0);
                if (abs(x1-x0) < es)
                    KQ = x1;
                    break;
                end
                x0 = x1;
            end
    end
    x = linspace(a, b, 100);
end