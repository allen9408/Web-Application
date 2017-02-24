function [m,std]=BayesCurFit(x, t, size, M, x_new)

a = 0.005;
b = 11.1;
phi_t=ones(size,M+1);
phi_sum = zeros(M+1,M+1);
s_inv = zeros(M+1,M+1);
I = eye(M+1);
tmp_m = zeros(M+1,1);
phi_new_t = ones(1,M+1);
for i=1:1:M
    phi_t(1:size,i+1)=x(1,1:size)'.^i;
end
phi = phi_t';
for i=1:1:size
    tmp=phi(1:M+1,i)*phi_t(i,1:M+1);
    phi_sum = phi_sum + tmp;
end
s_inv = a*I + b*phi_sum;
s = inv(s_inv)
% test new value
for i=1:1:M
	phi_new_t(1,i+1) = x_new^i;
end
phi_new = phi_new_t';

s_2 = b^(-1) + phi_new_t/s_inv*phi_new;
for i=1:1:size
    tmp = phi(1:M+1,i)*t(1,i);
    tmp_m = tmp_m + tmp;
end
m = b*phi_new_t/s_inv*tmp_m;
std=s_2;
end