clear all;
clc;
dt = 0.01;                     % 绘图间隔
T = -10 : dt : 10;             % 绘图时刻
f = 0.5.*(1+cos(T));           % 原函数

subplot(3, 2, 1)
plot(T, f, 'b'), axis([(min(T)) (max(T)) (min(f)) (max(f))]), title('f(t)=0.5(1+cos(t))原函数'), xlabel('t'), ylabel('f(t)');

wm = 2;                   % 信号带宽
wc = 1.2*wm;              % 滤波器截止频率
Ts = 1;                   % 采样间隔
Fs = 1/Ts;                % 采样频率
ws = 2*pi/Ts;             % 采样角频率
N = 100;                  % 滤波器时域采样点数
n = -N:N;
nTs = n.*Ts;              % 采样数据的采样时间
fs = 0.5.*(1+cos(nTs));   % 函数的采样点
% Wc=wm*0.9999/wm;          % wc=1.2*wm 超出范围 无需滤波
% [b,a]=butter(4,Wc,'low'); % 四阶的巴特沃斯低通滤波
% fs=filter(b,a,fs);
Dt = 0.01;                % 恢复信号采样间隔
t = -10:Dt:10;            % 恢复信号采样时刻
fa = fs*sinc(Fs.*(ones(length(nTs),1).*(t) - nTs'*ones(1,length((t)))));
subplot(3, 2, 3)
plot(t, fa, 'b'), title('f(t)=0.5(1+cos(t)),dt=1s 重建fa(t)结果'), xlabel('t'), ylabel('fa(t)');
error = abs(fa-f);
subplot(3, 2, 4)
plot(t, error, 'b'), title('f(t)=0.5(1+cos(t)),dt=1s 重建误差'), xlabel('t'), ylabel('error');

wm = 2;                   % 信号带宽
wc = 1.2*wm;              % 滤波器截止频率
Ts = 2;                   % 采样间隔
Fs = 1/Ts;                % 采样频率
ws = 2*pi/Ts;             % 采样角频率
N = 100;                  % 滤波器时域采样点数
n = -N:N;
nTs = n.*Ts;              % 采样数据的采样时间
fs = 0.5.*(1+cos(nTs));   % 函数的采样点
% Wc=wm*0.9999/wm;          % wc=1.2*wm 超出范围 无需滤波
% [b,a]=butter(4,Wc,'low'); % 四阶的巴特沃斯低通滤波
% fs=filter(b,a,fs);
Dt = 0.01;                % 恢复信号采样间隔
t = -10:Dt:10;            % 恢复信号采样时刻
fa = fs*sinc(Fs.*(ones(length(nTs),1).*(t) - nTs'*ones(1,length((t)))));
subplot(3, 2, 5)
plot(t, fa, 'b'), title('f(t)=0.5(1+cos(t)),dt=2s 重建fa(t)结果'), xlabel('t'), ylabel('fa(t)');
error = abs(fa-f);
subplot(3, 2, 6)
plot(t, error, 'b'), title('f(t)=0.5(1+cos(t)),dt=2s 重建误差'), xlabel('t'), ylabel('error');