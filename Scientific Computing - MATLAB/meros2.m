clear;

h = 4;    % 2,3,4
n = 1000; % 10,100,1000

A = toeplitz([h,-1,zeros(1,n-2)]);
W = randn(n,1);
W = W/norm(W);
H = W(n:-1:1);
real_x = randn(n,1);
b = (A+W*transpose(H)) * real_x;

cond_A = cond(A);

f1 = @() iterative_refinement(A,W,H,real_x,b);
f2 = @() SMW_dp(A,W,H,real_x,b);
f3 = @() SMW_sp_iter_ref(A,W,H,real_x,b);

%t1 = timeit(f1);
%t2 = timeit(f2);
%t3 = timeit(f3);

%[k,x,abs_err] = iterative_refinement(A,W,H,real_x,b);
%[x,abs_err] = SMW_dp(A,W,H,real_x,b);
%[k,x,abs_err] = SMW_sp_iter_ref(A,W,H,real_x,b);