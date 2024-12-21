function [x1, n] = lap(app, fx, fp, a, b, saiso)
    % Chuyển đổi chuỗi thành hàm
    fx = str2func(['@(x)', fx]);
    fp = str2func(['@(x)', fp]);

    n = 0;
    x0 = (a + b) / 2;

    while (1)
        % Tính giá trị mới của x
        x1 = x0 - fx(x0) / fp(x0);
        n = n + 1;

        % Kiểm tra điều kiện dừng
        if (abs(x1 - x0) < saiso)
            break;
        end

        % Kiểm tra x1 nằm trong khoảng [a, b]
        if (x1 < a || x1 > b)
            error('Phương trình không hội tụ trong khoảng [a, b].');
        end

        % Kiểm tra số lần lặp
        if (n > 1000)
            error('Số lần lặp vượt quá giới hạn.');
        end

        % Cập nhật giá trị x0
        x0 = x1;
    end
end
