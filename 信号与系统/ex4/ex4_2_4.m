%%%%%% H1 %%%%%%
b = [1 0];
a = [1 -0.8];

subplot(7, 2, 1)
zplane(b, a)
n = 60;
[h, k] = impz(b, a, n);
subplot(7, 2, 2)
plot(k, h)
title("h_1(k)");
xlabel("k");ylabel("h_1(k)");

%%%%%% H2 %%%%%%
b = [1 0];
a = [1 -1];

subplot(7, 2, 3)
zplane(b, a)
n = 60;
[h, k] = impz(b, a, n);
subplot(7, 2, 4)
plot(k, h)
title("h_2(k)");
xlabel("k");ylabel("h_2(k)");

%%%%%% H3 %%%%%%
b = [1 0];
a = [1 -1.2];

subplot(7, 2, 5)
zplane(b, a)
n = 60;
[h, k] = impz(b, a, n);
subplot(7, 2, 6)
plot(k, h)
title("h_3(k)");
xlabel("k");ylabel("h_3(k)");

%%%%%% H4 %%%%%%
b = [1 0];
a = [1 0.8];

subplot(7, 2, 7)
zplane(b, a)
n = 60;
[h, k] = impz(b, a, n);
subplot(7, 2, 8)
plot(k, h)
title("h_4(k)");
xlabel("k");ylabel("h_4(k)");

%%%%%% H5 %%%%%%
b = [0 1 0];
a = [1 -1.2 0.72];

subplot(7, 2, 9)
zplane(b, a)
n = 60;
[h, k] = impz(b, a, n);
subplot(7, 2, 10)
plot(k, h)
title("h_5(k)");
xlabel("k");ylabel("h_5(k)");

%%%%%% H6 %%%%%%
b = [0 1 0];
a = [1 -1.6 1];

subplot(7, 2, 11)
zplane(b, a)
n = 60;
[h, k] = impz(b, a, n);
subplot(7, 2, 12)
plot(k, h)
title("h_6(k)");
xlabel("k");ylabel("h_6(k)");

%%%%%% H7 %%%%%%
b = [0 1 0];
a = [1 -2 1.36];

subplot(7, 2, 13)
zplane(b, a)
n = 60;
[h, k] = impz(b, a, n);
subplot(7, 2, 14)
plot(k, h)
title("h_7(k)");
xlabel("k");ylabel("h_7(k)");