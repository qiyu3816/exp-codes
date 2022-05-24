gray = imread('electric.jpg');
figure(), imshow(gray);

gau = imnoise(gray, 'gauss', 0.05); % ��Ӹ�˹����
figure, imshow(gau);
J = imnoise(gau, 'salt & pepper', 0.05); % ��ӽ�������
ave1 = fspecial('average', 3); % ����3��3�ľ�ֵģ��
ave2 = fspecial('average', 5); % ����5��5�ľ�ֵģ��
K = filter2(ave1, J) / 255; % ��ֵ�˲�3��3
L = filter2(ave2, J) / 255; % ��ֵ�˲�5��5
M = medfilt2(J, [3 3]); % ��ֵ�˲�3��3ģ��
N = medfilt2(J, [4 4]); % ��ֵ�˲�4��4ģ��

figure, imshow(J);
figure, imshow(K);
figure, imshow(L);
figure, imshow(M);
figure, imshow(N);