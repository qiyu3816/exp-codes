clear all;
clc;
T = 0.01;
t = -10 : T : 10;
N = 500;
W = 10 * pi;
n = -N : N;
w = n * W / N;
f1 = exp(-t).*stepfun(t, 0);
f2 = exp(-t / 2.0).*stepfun(t, 0);

conv_f = conv(f1, f2);
t1 = linspace(-10, 10, length(conv_f));

f = (exp(-t) - exp(-t / 2.0)).*stepfun(t, 0);
F = T * f * exp(-1i * t'* w);
F_w = abs(F);
P_w = angle(F);

% 绘制调用conv计算出的卷积
% 进行拉伸和压缩之后画出
subplot(1, 4, 1)
plot(t1 * 2, -conv_f * 0.005, 'b'), axis([(min(t1)) (max(t1)) (min(-conv_f * 0.005)) (max(-conv_f * 0.005))]), title('conv-f5原函数'), xlabel('t'), ylabel('f');

subplot(1, 4, 2)
plot(t, f, 'b'), axis([(min(t)) (max(t)) (min(f)) (max(f))]), title('f5原函数'), xlabel('t'), ylabel('f');

subplot(1, 4, 3)
plot(w, F_w, 'b'), axis([(min(w)) (max(w)) (min(F_w)) (max(F_w))]), title('F5_w幅频'), xlabel('w'), ylabel('F');

subplot(1, 4, 4)
plot(w, P_w, 'b'), axis([(min(w)) (max(w)) (min(P_w)) (max(P_w))]), title('F5_w相频'), xlabel('w'), ylabel('P');