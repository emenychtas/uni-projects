function [ x,abs_err ] = SMW_dp( A,W,H,real_x,b )
    inv_A = inv(A);
    inv_AE = inv_A - (inv_A*W*transpose(H)*inv_A) / (1+transpose(H)*inv_A*W);
    
    x = inv_AE * b;
    abs_err = norm(real_x - x, Inf);
end