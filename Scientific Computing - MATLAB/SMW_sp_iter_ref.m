function [ k,x,abs_err ] = SMW_sp_iter_ref( A,W,H,real_x,b )
    AE = A + W * transpose(H);
    inv_A = inv(single(A));
    inv_AE = inv_A - (inv_A*W*transpose(H)*inv_A) / (1+transpose(H)*inv_A*W);

    k = 1;
    x{k} = double(inv_AE * b);
    abs_err{k} = norm(real_x - x{k}, Inf);
    
    while (abs_err{k} >= 10^-6)
       r{k+1} = b - AE*x{k};
       z{k+1} = double(inv_AE * r{k+1});
       x{k+1} = x{k} + z{k+1};
       abs_err{k+1} = norm(real_x - x{k+1}, Inf);

       k = k + 1;
    end

    if isnan(abs_err{k})
        fprintf('No convergence.\n');
    else
        fprintf('Convergence achieved.\n');
    end
end