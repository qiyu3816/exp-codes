clear all;
clc;
dt = 0.01;                     % ��ͼ���
T = -10 : dt : 10;             % ��ͼʱ��
N = 500;                       % ���ַ�Χ
W = 6 * pi;                    % ��ֹƵ��
n = -N : N;
w = n * W / N;                 % ���ɻ��ֵ�
f = 0.5.*(1+cos(T));           % ԭ����
F = dt * f * exp(-1i * T'* w); % ԭ��������Ҷ�任
F_w = abs(F);                  % ԭ������Ƶ����

subplot(4, 2, 1)
plot(T, f, 'b'), axis([(min(T)) (max(T)) (min(f)) (max(f))]), title('f(t)=0.5(1+cos(t))ԭ����'), xlabel('t'), ylabel('f(t)');

subplot(4, 2, 2)
plot(w, F_w, 'b'), axis([(min(w)) (max(w)) (min(F_w)) (max(F_w))]), title('f(t)=0.5(1+cos(t))������'), xlabel('w'), ylabel('An');

dt = 0.5;               % �������
Ts = -10:dt:10;         % ����ʱ��
fs = 0.5.*(1+cos(Ts));
subplot(4, 2, 3)
stem(Ts, fs), title('f(t)=0.5(1+cos(t)),dt=0.5s�������'), xlabel('t'), ylabel('fs(t)');
F = dt * fs * exp(-1i * Ts'* w); % dt=0.5s ������������Ҷ�任
F_w = abs(F);                    % dt=0.5s ����������Ƶ����
subplot(4, 2, 4)
plot(w, F_w, 'b'), axis([(min(w)) (max(w)) (min(F_w)) (max(F_w))]), title('f(t)=0.5(1+cos(t)),dt=0.5s ������'), xlabel('w'), ylabel('An');

dt = 1;                 % �������
Ts = -10:dt:10;         % ����ʱ��
fs = 0.5.*(1+cos(Ts));
subplot(4, 2, 5)
stem(Ts, fs), title('f(t)=0.5(1+cos(t)),dt=1s�������'), xlabel('t'), ylabel('fs(t)');
F = dt * fs * exp(-1i * Ts'* w); % dt=1s ������������Ҷ�任
F_w = abs(F);                    % dt=1s ����������Ƶ����
subplot(4, 2, 6)
plot(w, F_w, 'b'), axis([(min(w)) (max(w)) (min(F_w)) (max(F_w))]), title('f(t)=0.5(1+cos(t)),dt=1s ������'), xlabel('w'), ylabel('An');

dt = 2;                 % �������
Ts = -10:dt:10;         % ����ʱ��
fs = 0.5.*(1+cos(Ts));
subplot(4, 2, 7)
stem(Ts, fs), title('f(t)=0.5(1+cos(t)),dt=2s�������'), xlabel('t'), ylabel('fs(t)');
F = dt * fs * exp(-1i * Ts'* w); % dt=2s ������������Ҷ�任
F_w = abs(F);                    % dt=2s ����������Ƶ����
subplot(4, 2, 8)
plot(w, F_w, 'b'), axis([(min(w)) (max(w)) (min(F_w)) (max(F_w))]), title('f(t)=0.5(1+cos(t)),dt=2s ������'), xlabel('w'), ylabel('An');