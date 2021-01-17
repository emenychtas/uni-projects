n1 = [200:200:1400];
n2 = [250:200:1750];
deg = 4;

% X = qr(A)

[c_x,t_x_real1,mu_x] = Tx(n1,deg);
t_x_polyval1 = zeros(1,length(n1));
for i = 1:length(n1)
    t_x_polyval1(i) = polyval(c_x,n1(i),[],mu_x);
end

t_x_real2 = zeros(1,length(n2));
t_x_polyval2 = zeros(1,length(n2));
for i = 1:length(n2)
    A = randn(n2(i));
    f = @() qr(A);
    t_x_real2(i) = timeit(f);
    t_x_polyval2(i) = polyval(c_x,n2(i),[],mu_x);
end

% [Q,R] = qr(A)

[c_qr,t_qr_real1,mu_qr] = Tqr(n1,deg);
t_qr_polyval1 = zeros(1,length(n1));
for i = 1:length(n1)
    t_qr_polyval1(i) = polyval(c_qr,n1(i),[],mu_qr);
end

t_qr_real2 = zeros(1,length(n2));
t_qr_polyval2 = zeros(1,length(n2));
for i = 1:length(n2)
    A = randn(n2(i));
    f = @() qr(A);
    t_qr_real2(i) = timeit(f,2);
    t_qr_polyval2(i) = polyval(c_qr,n2(i),[],mu_qr);
end

% PLOTS

figure('Name','X = qr(A) for n = [200:200:1400]');
plot(n1,t_x_real1,'+',n1,t_x_polyval1,'--');
figure('Name','X = qr(A) for n = [250:200:1750]');
plot(n2,t_x_real2,'+',n2,t_x_polyval2,'--');

figure('Name','[Q,R] = qr(A) for n = [200:200:1400]');
plot(n1,t_qr_real1,'+',n1,t_qr_polyval1,'--');
figure('Name','[Q,R] = qr(A) for n = [250:200:1750]');
plot(n2,t_qr_real2,'+',n2,t_qr_polyval2,'--');