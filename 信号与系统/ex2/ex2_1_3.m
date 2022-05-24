clear all;
clc;
T = 0.01;
t = -10 : T : 10;
N = 500;
W = 10 * pi;
n = -N : N;
w = n * W / N;
f = exp(-t + 2.0).*stepfun(t - 2.0, 0);
F = T * f * exp(-1i * t'* w);
F_w = abs(F);
P_w = angle(F);

subplot(1, 3, 1)
plot(t, f, 'b'), axis([(min(t)) (max(t)) (min(f)) (max(f))]), title('f3Ô­º¯Êý'), xlabel('t'), ylabel('f');

subplot(1, 3, 2)
plot(w, F_w, 'b'), axis([(min(w)) (max(w)) (min(F_w)) (max(F_w))]), title('F3_w·ùÆµ'), xlabel('w'), ylabel('F');

subplot(1, 3, 3)
plot(w, P_w, 'b'), axis([(min(w)) (max(w)) (min(P_w)) (max(P_w))]), title('F3_wÏàÆµ'), xlabel('w'), ylabel('P');