t = (-20 : 0.01 : 20);
% sin(t) �� sin(pi/4*t) �����ں���
x1 = sin(t) + sin(pi / 4 .* t);
plot(t, x1, 'b'), axis([(min(t) - 0.25) (max(t) + 0.25) (min(x1) - 1) (max(x1) + 1)]), title('x(t)'), xlabel('t [s]'), ylabel('x(t)');