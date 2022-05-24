t = (0 : 0.01 : 20);
% 理论零状态响应
yzs1 = (exp(-t) - exp(-2 * t) - t .* exp(-2 * t)) .* heaviside(t);

% 调用内置函数得出零状态响应
model = tf([1], [1, 3, 2]);
f = exp(-2 * t) .* heaviside(t);
y = lsim(model, f, t);

subplot(1, 2, 1)
plot(t, yzs1, 'b'), axis([(min(t) - 0.25) (max(t) + 0.25) (min(yzs1) - 1) (max(yzs1) + 1)]), title('yzs1(t)'), xlabel('t [s]'), ylabel('yzs1(t)');

subplot(1, 2, 2)
plot(t, y, 'b'), axis([(min(t) - 0.25) (max(t) + 0.25) (min(y) - 1) (max(y) + 1)]), title('lsim_y(t)'), xlabel('t [s]'), ylabel('lsim_y(t)');