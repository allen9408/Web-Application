function [w_init, err_1, w_final, err_final, times]=BP(x, t, rate, max_times, target)
% Initialize v's and w's
w = 2*rand(1,2,'double') - 1;
w_init = w;
v = 2*rand(2,2,'double') - 1;
b = 2*rand(1,2,'double') - 1;
c = 2*rand(1,1,'double') - 1;
hnode = zeros(1,2);
w_delta = zeros(1,2);
v_delta = zeros(2,2);
b_delta = zeros(1,2);
times = 0;
err_1 = 0;
w_final = zeros(1,2);
y = zeros(1,4);
err = 0;
% start traning
for k=1:1:max_times
    err = 0;
    w_delta = zeros(1,2);
    v_delta = zeros(2,2);
    b_delta = zeros(1,2);
    c_delta = 0;
    for l = 1:1:4
        % calculate hidden layer
        hnode(1,1) = f(v(1,1)*x(l,1) + v(2,1)*x(l,2) + (-1)*b(1,1));
        hnode(1,2) = f(v(1,2)*x(l,1) + v(2,2)*x(l,2) + (-1)*b(1,2));
        % calculate output layer
        y(1,l) = f(w(1,1)*hnode(1,1)+ w(1,2)*hnode(1,2) + (-1)*c);
        err = err + 0.5*(t(1,l)-y(1,l))^2;
        
        ddd = (t(1,l)-y(1,l))*f_prime(y(1,l));
        % calculate delta_w
        w_delta(1,1) = w_delta(1,1) + rate*hnode(1,1)* ddd;
        w_delta(1,2) = w_delta(1,2) + rate*hnode(1,2)* ddd;
        c_delta      = c_delta      + rate*(-1)      * ddd;
        % calculate delta_v
        v_delta(1,1) = v_delta(1,1) + rate* ddd *w(1,1)*f_prime(hnode(1,1))*x(l,1);
        v_delta(1,2) = v_delta(1,2) + rate* ddd *w(1,2)*f_prime(hnode(1,2))*x(l,1);
        v_delta(2,1) = v_delta(2,1) + rate* ddd *w(1,1)*f_prime(hnode(1,1))*x(l,2);
        v_delta(2,2) = v_delta(2,2) + rate* ddd *w(1,2)*f_prime(hnode(1,2))*x(l,2);
        b_delta(1,1) = b_delta(1,1) + rate* ddd *w(1,1)*f_prime(hnode(1,1))*(-1);
        b_delta(1,2) = b_delta(1,2) + rate* ddd *w(1,2)*f_prime(hnode(1,2))*(-1);
    end
    % output first-batch error
    if (k == 1)
        err_1 = err;
    end
    % count times
    times = times + 1;
    if (err < target)
        break;
    end
    % update v and w
    w = w + w_delta;
    v = v + v_delta;
    b = b + b_delta;
    c = c + c_delta;
end
err_final = err;
w_final = w;
end

function y = f(x)
y = 1/(1+exp(-x));
end

function y = f_prime(x)
y = f(x)*(1-f(x));
end