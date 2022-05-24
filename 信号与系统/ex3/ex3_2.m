clear all;
clc;
dt = 0.01;                     % ��ͼ���
T = -10 : dt : 10;             % ��ͼʱ��
f = 0.5.*(1+cos(T));           % ԭ����

subplot(3, 2, 1)
plot(T, f, 'b'), axis([(min(T)) (max(T)) (min(f)) (max(f))]), title('f(t)=0.5(1+cos(t))ԭ����'), xlabel('t'), ylabel('f(t)');

wm = 2;                   % �źŴ���
wc = 1.2*wm;              % �˲�����ֹƵ��
Ts = 1;                   % �������
Fs = 1/Ts;                % ����Ƶ��
ws = 2*pi/Ts;             % ������Ƶ��
N = 100;                  % �˲���ʱ���������
n = -N:N;
nTs = n.*Ts;              % �������ݵĲ���ʱ��
fs = 0.5.*(1+cos(nTs));   % �����Ĳ�����
% Wc=wm*0.9999/wm;          % wc=1.2*wm ������Χ �����˲�
% [b,a]=butter(4,Wc,'low'); % �Ľ׵İ�����˹��ͨ�˲�
% fs=filter(b,a,fs);
Dt = 0.01;                % �ָ��źŲ������
t = -10:Dt:10;            % �ָ��źŲ���ʱ��
fa = fs*sinc(Fs.*(ones(length(nTs),1).*(t) - nTs'*ones(1,length((t)))));
subplot(3, 2, 3)
plot(t, fa, 'b'), title('f(t)=0.5(1+cos(t)),dt=1s �ؽ�fa(t)���'), xlabel('t'), ylabel('fa(t)');
error = abs(fa-f);
subplot(3, 2, 4)
plot(t, error, 'b'), title('f(t)=0.5(1+cos(t)),dt=1s �ؽ����'), xlabel('t'), ylabel('error');

wm = 2;                   % �źŴ���
wc = 1.2*wm;              % �˲�����ֹƵ��
Ts = 2;                   % �������
Fs = 1/Ts;                % ����Ƶ��
ws = 2*pi/Ts;             % ������Ƶ��
N = 100;                  % �˲���ʱ���������
n = -N:N;
nTs = n.*Ts;              % �������ݵĲ���ʱ��
fs = 0.5.*(1+cos(nTs));   % �����Ĳ�����
% Wc=wm*0.9999/wm;          % wc=1.2*wm ������Χ �����˲�
% [b,a]=butter(4,Wc,'low'); % �Ľ׵İ�����˹��ͨ�˲�
% fs=filter(b,a,fs);
Dt = 0.01;                % �ָ��źŲ������
t = -10:Dt:10;            % �ָ��źŲ���ʱ��
fa = fs*sinc(Fs.*(ones(length(nTs),1).*(t) - nTs'*ones(1,length((t)))));
subplot(3, 2, 5)
plot(t, fa, 'b'), title('f(t)=0.5(1+cos(t)),dt=2s �ؽ�fa(t)���'), xlabel('t'), ylabel('fa(t)');
error = abs(fa-f);
subplot(3, 2, 6)
plot(t, error, 'b'), title('f(t)=0.5(1+cos(t)),dt=2s �ؽ����'), xlabel('t'), ylabel('error');