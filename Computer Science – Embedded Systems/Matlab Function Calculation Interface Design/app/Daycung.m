function [c, n] = Daycung(fx, x0, x1, saiso)
    % Convert the input string to a function handle
    fx = str2func(['@(x)', fx]);
    
    n = 0;    % Number of iterations
    c0 = x0;  % Initial value of x0
    c1 = x1;  % Initial value of x1
    
    while (1)
        % Calculate the Secant slope and update c
        slope = (fx(c1) - fx(c0)) / (c1 - c0);
        c = c1 - fx(c1) / slope;
        
        % Check if the precision condition is met
        if (abs(c - c1) < saiso)
            break;
        end
        
        % Update values for the next iteration
        c0 = c1;
        c1 = c;
        
        % Update the iteration count
        n = n + 1;
    end
end
