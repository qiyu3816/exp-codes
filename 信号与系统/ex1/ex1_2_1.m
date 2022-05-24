plotLines = 2;
plotColoums = 2;

subplot(plotLines, plotColoums, 1)
% 绘制最初的门函数 宽1 横坐标中心0 幅度1
t = (-1 : 0.01 : 1);
x1 = rectpuls(t, 1);
plot(t, x1, 'b'), axis([(min(t) - 0.25) (max(t) + 0.25) (min(x1) - 1) (max(x1) + 1)]), title('G1(t)'), xlabel('t [s]'), ylabel('G1(t)');

subplot(plotLines, plotColoums, 2)
t = (-1 : 0.01 : 1);
x2 = rectpuls(2 * t, 1);
plot(t, x2, 'b'), axis([(min(t) - 0.25) (max(t) + 0.25) (min(x2) - 1) (max(x2) + 1)]), title('G1(2t)'), xlabel('t [s]'), ylabel('G1(2t)');

subplot(plotLines, plotColoums, 3)
t = (-2 : 0.01 : 2);
x3 = rectpuls(t / 2, 1);
plot(t, x3, 'b'), axis([(min(t) - 0.25) (max(t) + 0.25) (min(x3) - 1) (max(x3) + 1)]), title('G1(t/2)'), xlabel('t [s]'), ylabel('G1(t/2)');

subplot(plotLines, plotColoums, 4)
t = (-1 : 0.01 : 1);
x4 = rectpuls(1 - 2 * t, 1);
plot(t, x4, 'b'), axis([(min(t) - 0.25) (max(t) + 0.25) (min(x4) - 1) (max(x4) + 1)]), title('G1(1-2t)'), xlabel('t [s]'), ylabel('G1(1-2t)');