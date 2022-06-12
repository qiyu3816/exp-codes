I = imread('v1_red.jpg');
gray = rgb2gray(I);
imwrite(gray, 'infer_near.jpg');

% 二值化
% I = imread('xun.png');
% I = rgb2gray(I);
% [M,N] = size(I);
% target = zeros(size(I));
% for i=1:M
%     for j=1:N
%         if I(i, j) < 70
%             target(i, j) = 255;
%         end
%     end
% end
% imwrite(target, 'xun1.png');

% resize
% I = imread('xun.jpg');
% B = imresize(I, [2604, 2600]);
% imwrite(B, 'xun1.png');