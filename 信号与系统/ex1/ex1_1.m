plotLines = 1;
plotColoums = 3;

subplot(plotLines, plotColoums, 1)
% 绘制第一个波形
t = (-1 : 0.01 : 4);
x1 = cos(2 .* pi .* t) .* (heaviside(t) - heaviside(t - 3));
plot(t, x1, 'g'), axis([min(t) max(t) (min(x1) - 1) (max(x1) + 1)]), title('1.1'), xlabel('t [s]'), ylabel('x1(t)');

subplot(plotLines, plotColoums, 2)
% 绘制第二个波形
t = (-1 : 0.01 : 10);
x2 = (exp(-t) - exp(3 .* (-t))) .* heaviside(t);
plot(t, x2, 'r'), axis([min(t) max(t) (min(x2) - 1) (max(x2) + 1)]), title('1.2'), xlabel('t [s]'), ylabel('x2(t)');

subplot(plotLines, plotColoums, 3)
% 绘制第三个波形——门函数
t = (-1 : 0.01 : 1);
x3 = rectpuls(t, 1);
plot(t, x3, 'b'), axis([(min(t) - 0.25) (max(t) + 0.25) (min(x3) - 1) (max(x3) + 1)]), title('1.3'), xlabel('t [s]'), ylabel('x3(t)');