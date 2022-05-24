syms k;
f = power(2, k - 1) * heaviside(k);
disp(ztrans(f));