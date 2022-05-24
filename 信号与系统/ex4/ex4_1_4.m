syms s;
H = (s - 1) / (s * s + 3 * s + 2);
b = [0 1 -1]; % ����
a = [1 3 2];  % ��ĸ

[z, p, k] = tf2zp(b, a);
fvtool(b, a, 'polezero')
text(real(z) + .1, imag(z), 'Zero')
text(real(p) + .1, imag(p), 'Pole')

sys = tf(b, a);
t = 0:0.1:10;
y = impulse(sys, t);
subplot(1, 3, 1)
plot(t, y), title('H(s)ϵͳ��λ�弤��Ӧ'), xlabel('t'), ylabel('h(t)')

w = logspace(-1,1);
h = freqs(b,a,w);
mag = abs(h);
phase = angle(h);
phasedeg = phase*180/pi;

subplot(1, 3, 2)
loglog(w,mag)
grid on
title('H(s)��Ƶ��Ӧ')
xlabel('Frequency (rad/s)')
ylabel('Magnitude')

subplot(1, 3, 3)
semilogx(w,phasedeg)
grid on
title('H(s)��Ƶ��Ӧ')
xlabel('Frequency (rad/s)')
ylabel('Phase (degrees)')