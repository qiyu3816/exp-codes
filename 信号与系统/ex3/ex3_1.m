clear all;
clc;
dt = 0.01;                     % 绘图间隔
T = -10 : dt : 10;             % 绘图时刻
N = 500;                       % 积分范围
W = 6 * pi;                    % 截止频率
n = -N : N;
w = n * W / N;                 % 生成积分点
f = 0.5.*(1+cos(T));           % 原函数
F = dt * f * exp(-1i * T'* w); % 原函数傅里叶变换
F_w = abs(F);                  % 原函数幅频曲线

subplot(4, 2, 1)
plot(T, f, 'b'), axis([(min(T)) (max(T)) (min(f)) (max(f))]), title('f(t)=0.5(1+cos(t))原函数'), xlabel('t'), ylabel('f(t)');

subplot(4, 2, 2)
plot(w, F_w, 'b'), axis([(min(w)) (max(w)) (min(F_w)) (max(F_w))]), title('f(t)=0.5(1+cos(t))幅度谱'), xlabel('w'), ylabel('An');

dt = 0.5;               % 采样间隔
Ts = -10:dt:10;         % 采样时刻
fs = 0.5.*(1+cos(Ts));
subplot(4, 2, 3)
stem(Ts, fs), title('f(t)=0.5(1+cos(t)),dt=0.5s采样结果'), xlabel('t'), ylabel('fs(t)');
F = dt * fs * exp(-1i * Ts'* w); % dt=0.5s 抽样函数傅里叶变换
F_w = abs(F);                    % dt=0.5s 抽样函数幅频曲线
subplot(4, 2, 4)
plot(w, F_w, 'b'), axis([(min(w)) (max(w)) (min(F_w)) (max(F_w))]), title('f(t)=0.5(1+cos(t)),dt=0.5s 幅度谱'), xlabel('w'), ylabel('An');

dt = 1;                 % 采样间隔
Ts = -10:dt:10;         % 采样时刻
fs = 0.5.*(1+cos(Ts));
subplot(4, 2, 5)
stem(Ts, fs), title('f(t)=0.5(1+cos(t)),dt=1s采样结果'), xlabel('t'), ylabel('fs(t)');
F = dt * fs * exp(-1i * Ts'* w); % dt=1s 抽样函数傅里叶变换
F_w = abs(F);                    % dt=1s 抽样函数幅频曲线
subplot(4, 2, 6)
plot(w, F_w, 'b'), axis([(min(w)) (max(w)) (min(F_w)) (max(F_w))]), title('f(t)=0.5(1+cos(t)),dt=1s 幅度谱'), xlabel('w'), ylabel('An');

dt = 2;                 % 采样间隔
Ts = -10:dt:10;         % 采样时刻
fs = 0.5.*(1+cos(Ts));
subplot(4, 2, 7)
stem(Ts, fs), title('f(t)=0.5(1+cos(t)),dt=2s采样结果'), xlabel('t'), ylabel('fs(t)');
F = dt * fs * exp(-1i * Ts'* w); % dt=2s 抽样函数傅里叶变换
F_w = abs(F);                    % dt=2s 抽样函数幅频曲线
subplot(4, 2, 8)
plot(w, F_w, 'b'), axis([(min(w)) (max(w)) (min(F_w)) (max(F_w))]), title('f(t)=0.5(1+cos(t)),dt=2s 幅度谱'), xlabel('w'), ylabel('An');