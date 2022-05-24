t1 = -3 : 0.001 : 3;
y1 = square(pi.*t1 + pi / 2);
y1 = (y1 > 0)

subplot(1, 2, 1)
plot(t1, y1), axis([(min(t1) - 0.25) (max(t1) + 0.25) min(y1) max(y1)]), title('ԭ���ڽ�Ծ�ź�'), xlabel('t [s]'), ylabel('y1(t)');

% subplot(1, 2, 2)
% n1 = 1 : 1 : 3; % ���Ǹ���Ҷ����ǰ����
% y2 = 1 / 2;
% for n = n1
%     y2 = y2 + 2 / n / pi * sin(n * pi / 2) * cos (n * pi .* t1);
% end
% plot(t1, y2), axis([(min(t1) - 0.25) (max(t1) + 0.25) min(y2) max(y2)]), title('���Ǹ���Ҷ����ǰ3��'), xlabel('t [s]'), ylabel('y2(t)');

% subplot(1, 2, 2)
% n1 = 1 : 1 : 5; % ���Ǹ���Ҷ����ǰ����
% y2 = 1 / 2;
% for n = n1
%     y2 = y2 + 2 / n / pi * sin(n * pi / 2) * cos (n * pi .* t1);
% end
% plot(t1, y2), axis([(min(t1) - 0.25) (max(t1) + 0.25) min(y2) max(y2)]), title('���Ǹ���Ҷ����ǰ5��'), xlabel('t [s]'), ylabel('y2(t)');

subplot(1, 2, 2)
n1 = 1 : 1 : 3; % ָ������Ҷ����ǰ����
y2 = 0;
for n = n1
    y2 = y2 + sin(n * pi / 2) / n / pi * exp(1j * n * pi .* t1);
end
plot3(t1,real(y2),imag(y2)), axis([(min(t1) - 0.25) (max(t1) + 0.25) min(real(y2)) max(real(y2)) min(imag(y2)) max(imag(y2))]), title('ָ������Ҷ����ǰ3��'), xlabel('t [s]'), ylabel('real(y2(t))'), ylabel('image(y2(t))');

% subplot(1, 2, 2)
% n1 = 1 : 1 : 5; % ָ������Ҷ����ǰ����
% y2 = 0;
% for n = n1
%     y2 = y2 + sin(n * pi / 2) / n / pi * exp(1j * n * pi .* t1);
% end
% plot3(t1,real(y2),imag(y2)), axis([(min(t1) - 0.25) (max(t1) + 0.25) min(real(y2)) max(real(y2)) min(imag(y2)) max(imag(y2))]), title('ָ������Ҷ����ǰ5��'), xlabel('t [s]'), ylabel('real(y2(t))'), zlabel('image(y2(t))');
