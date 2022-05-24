syms s;
F1 = (4 * s + 5) / (s * s + 5 * s + 6);
F2 = (3 * s) / (s + 4) / (s + 2);
F3 = (s + 5) / s / (s * s + 2 * s + 5);
disp(ilaplace(F1));
disp(ilaplace(F2));
disp(ilaplace(F3));