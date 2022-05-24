t = (-3 : 0.01 : 5);
f1 = exp(-3 * t) .* heaviside(t);
f2 = exp(-t) .* heaviside(t);
x1 = - 1 / 2 * (exp(3 * (-t)) - exp(-t)) .* heaviside(t);
conv_x = conv(f1, f2);

% ���������Ƶ����ľ��
subplot(1, 2, 1)
plot(t, x1, 'b'), axis([(min(t) - 0.25) (max(t) + 0.25) (min(x1) - 1) (max(x1) + 1)]), title('x(t)'), xlabel('t [s]'), ylabel('x(t)');

% ���Ƶ���conv������ľ��
% �����Ľ������ά�ȱ����ԭ�����Ķ�����һ ���������˼��ĵ�����
% ���������ѹ��֮�󻭳�
subplot(1, 2, 2)
t1 = linspace(-3, 5, length(conv_x));
plot(t1 * 2, conv_x * 0.01, 'b'), axis([(min(t) - 0.25) (max(t) + 0.25) (min(conv_x / 100) - 1) (max(conv_x / 100) + 1)]), title('conv_x(t)'), xlabel('t [s]'), ylabel('conv_x(t)');