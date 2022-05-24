% 读入图像 转成灰度图
srcimg = imread('case1.jpg');
disp(size(srcimg));
channels = size(size(srcimg));
gray = srcimg;
if channels(1, 2) == 3 % case2.jpg本身就是灰度图像
    gray = rgb2gray(srcimg);
end

% （1）预处理 高斯平滑 OTSU计算全局阈值 二值化
gray = imgaussfilt(gray, 1);
% gray = medfilt2(gray, [5, 5]);
thresh = graythresh(gray);
bino = imbinarize(gray, thresh);

% （2）对二值图进行形态学操作 筛除噪点
sedisk15 = strel('disk', 15);
semine = [1 1 1 1 1 1 1 1 1 1 1;
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
diskOpen1 = imopen(bino, sedisk15);
sedisk10 = strel('disk', 10);
diskClose1 = imclose(diskOpen1, sedisk10);
seminClose1 = imclose(diskClose1, semine); 

srcsize = size(srcimg);
B = bwboundaries(seminClose1);
boundary = B{1};
cntErode = 0;
while 1
    B = bwboundaries(seminClose1);
    contourLengthMax = 0;
    idx = 1;
    for k = 1:length(B)
        boundary = B{k};
        if length(boundary) > contourLengthMax
            idx = k;
            contourLengthMax = length(boundary);
        end
    end
    boundary = B{idx};
    if length(boundary) > 0.85 * (srcsize(1, 1) * 1.41 * 2 + srcsize(1, 2) * 2)
        seminClose1 = imerode(seminClose1, sedisk10);
        cntErode = cntErode + 1;
        continue
    end
    break
end

% （3）保留最大的轮廓 并填充该轮廓
[M,N] = size(bino);
maxcontour = zeros(size(bino));
for p = 1:size(boundary)
    maxcontour(boundary(p, 1), boundary(p, 2)) = 1;
end
maxcontour = im2uint8(maxcontour);
maxcontour = imfill(maxcontour, 'holes');
while cntErode ~= 0
    maxcontour = imdilate(maxcontour, sedisk10);
    cntErode = cntErode - 1;
end

% （4）形态学处理 得到最终轮廓
semineDilate1 = imdilate(maxcontour, semine);
diskDilate1 = imdilate(semineDilate1, sedisk10);
semineErode1 = imerode(diskDilate1, semine);

% （5）显示过程与结果
subplot(2, 4, 1), imshow(gray), title('1 gaussian gray');
subplot(2, 4, 2), imshow(bino), title('2 bino after OTSU on 1');
subplot(2, 4, 3), imshow(diskOpen1), title('3 opened bino after 2');
subplot(2, 4, 4), imshow(diskClose1), title('4 closed bino after 3');
subplot(2, 4, 5), imshow(seminClose1), title('5 closed bino used se1 on 4');
subplot(2, 4, 6), imshow(semineDilate1), title('6 dilate on the largest contour in 5');
subplot(2, 4, 7), imshow(semineErode1), title('7 erode on the largest contour in 6');


B = bwboundaries(semineErode1);
boundary = B{1};
subplot(2, 4, 8)
imshow(gray)
hold on
plot(boundary(:, 2), boundary(:, 1), 'r'), title('8 result');
