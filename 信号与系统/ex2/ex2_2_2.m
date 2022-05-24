clear all;
clc;
T = 0.01;
t = -10 : T : 10;
N = 500;
W = 10 * pi;
n = -N : N;
w = n * W / N;
H = 40 ./ (1i.*w + 10 * sqrt(3));
F_w = abs(H);
P_w = angle(H);

subplot(1, 2, 1)
plot(w, F_w, 'b'), axis([(min(w)) (max(w)) (min(F_w)) (max(F_w))]), title('H_w∑˘∆µ'), xlabel('w'), ylabel('F');

subplot(1, 2, 2)
plot(w, P_w, 'b'), axis([(min(w)) (max(w)) (min(P_w)) (max(P_w))]), title('H_wœ‡∆µ'), xlabel('w'), ylabel('P');