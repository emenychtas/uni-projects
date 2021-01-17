function [ c, t, mu ] = Tqr( n, deg )
    t = zeros(1,length(n));
    
    for i = 1:length(n)
        A = randn(n(i));
        f = @() qr(A);
        t(i) = timeit(f,2);
    end
    
    [c,~,mu] = polyfit(n,t,deg);
end