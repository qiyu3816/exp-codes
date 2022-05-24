syms t;
f1 = exp(-2 * t) * heaviside(t);
f2 = sin(2 * t) * heaviside(t);
f3 = dirac(t) + exp(2 * t) * heaviside(t) - 4/ 3 * exp(-t) * heaviside(t);
disp(laplace(f1));
disp(laplace(f2));
disp(laplace(f3));