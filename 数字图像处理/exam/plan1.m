srcimg = imread('case1.jpg');
gray = rgb2gray(srcimg);

se = [1 1 1 1 1 1 1 1 1 1 1;
    0 1 1 1 1 1 1 1 1 1 0;
    0 0 1 1 1 1 1 1 1 0 0;
    0 0 0 1 1 1 1 1 0 0 0;
    0 0 0 0 1 1 1 0 0 0 0;
    0 0 0 0 0 1 0 0 0 0 0;
    0 0 0 0 1 1 1 0 0 0 0;
    0 0 0 1 1 1 1 1 0 0 0;
    0 0 1 1 1 1 1 1 1 0 0;
    0 1 1 1 1 1 1 1 1 1 0;
    1 1 1 1 1 1 1 1 1 1 1];
tophated = imtophat(gray, se);

figure(1), imshow(tophated);

% ¿≠∆’¿≠Àπ±ﬂ‘µºÏ≤‚
% [M,N]=size(doubleimg);
% lap=zeros(size(doubleimg));
% for x=2:M-1
%     for y=2:N-1
%         lap(x,y)=doubleimg(x+1,y)+doubleimg(x-1,y)+doubleimg(x,y+1)+doubleimg(x,y-1)-4*doubleimg(x,y);
%     end
% end
% lap=im2uint8(lap);

% canny±ﬂ‘µºÏ≤‚
% can = edge(gray, 'canny', 0.2);