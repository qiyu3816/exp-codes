I = imread('lake.tif');
whos I;
figure(1), imshow(I);

info = imfinfo('lake.tif');
disp(info);

imwrite(I, 'lake.jpg', 'quality', 5);
imwrite(I, 'lake.bmp');

mountain = imread('mountain.jpg');
sunset = imread('sunset.jpg');
info = imfinfo('mountain.jpg');
disp(info);
info = imfinfo('sunset.jpg');
disp(info);

figure(2), imshow(mountain);
figure(3), imshow(sunset);

gray = rgb2gray(I);
bino = imbinarize(gray);
figure(4), imshow(bino);

% I = imread('xun.png');
% I = rgb2gray(I);
% [M,N] = size(I);
% target = zeros(size(I));
% for i=1:M
%     for j=1:N
%         if I(i, j) < 40
%             target(i, j) = 255;
%         end
%     end
% end
% imwrite(target, 'xun1.png');
            