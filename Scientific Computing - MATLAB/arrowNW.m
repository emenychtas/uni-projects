function [ A ] = arrowNW( T, n )
    m = size(T,1);
    D = T + m * eye(m);
    
    B = ones(n,1);
    B(1) = 0;
    B = ones(n) - B*transpose(B);
    B(1,1) = 0;
    
    A = kron(eye(n),D) + kron(B,T);
end