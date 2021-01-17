myHash = 9683;

%m = 4; n = 20;
m = 4; n = 250;
%m = 8; n = 125;
%m = 8; n = 250;
%m = 16; n = 125;

rng(myHash);
T = full(sprand(m,m,0.6));
A = arrowNW(T,n);
[L,U] = lu(A);

%spy(A);
%spy(L);
%spy(U);

W = fliplr(eye(m*n));
B = W*A*transpose(W);
[LB,UB] = lu(B);

%spy(B);
%spy(LB);
%spy(UB);

fill = (nnz(L)+nnz(U)-m*n)/nnz(A);
fillB = (nnz(LB)+nnz(UB)-m*n)/nnz(B);

e = ones(m*n,1);
b = A*e;
Wb = W*b;

%A = sparse(A);
%B = sparse(B);

% A * x = b
f1 = @() A\b;
t1 = timeit(f1);
x1 = f1();
rerr1 = norm(e-x1,Inf)/norm(e,Inf);

% B * Wx = Wb
f2 = @() B\Wb;
t2 = timeit(f2);
Wx = f2();
x2 = transpose(W)*Wx;
rerr2 = norm(e-x2,Inf)/norm(e,Inf);