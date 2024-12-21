function x = GaussJordan(A, b)  
    [m, n] = size(A);
    AugmentedMatrix = [A, b];
    for i = 1:m
        pivot = AugmentedMatrix(i, i);
        AugmentedMatrix(i, :) = AugmentedMatrix(i, :) / pivot;
        for j = 1:m
            if j ~= i
                factor = AugmentedMatrix(j, i);
                AugmentedMatrix(j, :) = AugmentedMatrix(j, :) - factor * AugmentedMatrix(i, :);
            end
        end
    end
    x = AugmentedMatrix(:, end);
end
