t = (-3 : 0.01 : 5);
% sin(pi*t) 和 sin(2*pi*t) 周期函数
x1 = sin(pi .* t) + sin(2 * pi .* t);
plot(t, x1, 'b'), axis([(min(t) - 0.25) (max(t) + 0.25) (min(x1) - 1) (max(x1) + 1)]), title('x(t)'), xlabel('t [s]'), ylabel('x(t)');