function [ k,x,abs_err ] = iterative_refinement( A,W,H,real_x,b )
    E = W * transpose(H);
    inv_A = inv(A);

    k = 1;
    x{k} = ones(size(real_x,1),1);
    abs_err{k} = norm(real_x - x{k}, Inf);

    while (abs_err{k} >= 10^-6)
        x{k+1} = inv_A * (-E * x{k} + b);
        abs_err{k+1} = norm(real_x - x{k+1}, Inf);

        k = k + 1;
    end

    if isnan(abs_err{k})
        fprintf('No convergence.\n');
    else
        fprintf('Convergence achieved.\n');
    end
end