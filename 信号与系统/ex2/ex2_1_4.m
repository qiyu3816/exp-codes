clear all;
clc;
T = 0.01;
t = -10 : T : 10;
N = 500;
W = 10 * pi;
n = -N : N;
w = n * W / N;
f = exp(-t).*stepfun(t, 0).*cos(2.0 * t);
F = T * f * exp(-1i * t'* w);
F_w = abs(F);
P_w = angle(F);

subplot(1, 3, 1)
plot(t, f, 'b'), axis([(min(t)) (max(t)) (min(f)) (max(f))]), title('f4ԭ????'), xlabel('t'), ylabel('f');

subplot(1, 3, 2)
plot(w, F_w, 'b'), axis([(min(w)) (max(w)) (min(F_w)) (max(F_w))]), title('F4_w??Ƶ'), xlabel('w'), ylabel('F');

subplot(1, 3, 3)
plot(w, P_w, 'b'), axis([(min(w)) (max(w)) (min(P_w)) (max(P_w))]), title('F4_w??Ƶ'), xlabel('w'), ylabel('P');