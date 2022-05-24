% (1)
rgb_image=imread('flower.tiff'); %读取图像flower1.tif
fR=rgb_image(:,:,1); %获取图像的红色分量
fG=rgb_image(:,:,2); %获取图像的绿色分量
fB=rgb_image(:,:,3); %获取图像的蓝色分量
imwrite(fR, 'v1_red.jpg');
imwrite(fG, 'v1_green.jpg');
imwrite(fB, 'v1_blue.jpg');
figure(1)
subplot(1, 3, 1),imshow(fR) %分别显示图像
subplot(1, 3, 2),imshow(fG)
subplot(1, 3, 3),imshow(fB)

% (2)
yiq_image=rgb2ntsc(rgb_image);
fY=yiq_image(:,:,1); %图像flower1.tif的亮度
fI=yiq_image(:,:,2); %图像flower1.tif的色调
fQ=yiq_image(:,:,3); %图像flower1.tif的饱和度
figure(2),
subplot(1, 3, 1), imhist(fR), title('处理前R')
subplot(1, 3, 2), imhist(fG), title('处理前G')
subplot(1, 3, 3), imhist(fB), title('处理前B')
figure(3),
subplot(1, 3, 1), imshow(fY), title('处理前亮度')
subplot(1, 3, 2), imshow(fI), title('处理前色调')
subplot(1, 3, 3), imshow(fQ), title('处理前饱和度')
fR=histeq(fR,256); %对彩色图像的分量进行直方图均衡化
fG=histeq(fG,256);
fB=histeq(fB,256);
RGB_image=cat(3,fR,fG,fB); %将直方图均衡化后的彩色图像合并
YIQ_image=rgb2ntsc(RGB_image);
fY=YIQ_image(:,:,1); %处理后的图像flower1.tif的亮度
fI=YIQ_image(:,:,2); %处理后的图像flower1.tif的色调
fQ=YIQ_image(:,:,3); %处理后的图像flower1.tif的饱和度
figure(4),
subplot(1, 3, 1), imhist(fR), title('处理后R')
subplot(1, 3, 2), imhist(fG), title('处理后G')
subplot(1, 3, 3), imhist(fB), title('处理后B')
figure(5),
subplot(1, 3, 1), imshow(fY), title('处理后亮度')
subplot(1, 3, 2), imshow(fI), title('处理后色调')
subplot(1, 3, 3), imshow(fQ), title('处理后饱和度')
figure(6),imshow(RGB_image),title('处理后的彩色图像') %观察处理后的彩色图色度，亮度参照前面

% (3)
% f1=imread('v1_red.jpg');
% f2=imread('v1_green.jpg');
% f3=imread('v1_blue.jpg');
% f4=imread('infer_near.jpg'); % 红外图像！！！
% ture_color=cat(3,f1,f2,f3);
% figure,imshow(ture_color) %显示由红、绿、蓝三幅图合成的彩色图
% false_color=cat(3,f4,f2,f3); %用近红外图像代替R分量
% figure,imshow(false_color) %显示由近红外、绿、蓝三幅图合成的假彩色图

% (4)
f=imread('lena.jpg');
cut_1=imadjust(f,[0.0925 0.5],[0.0925 0.5]);%提取灰度在16-128之间的像素
cut_2=imadjust(f,[0.5 1],[0.5 1]); %提取灰度在128-256之间的像素
figure(7)
subplot(2, 2, 1),imshow(cut_1),title('cut_1')
subplot(2, 2, 2),imshow(cut_1),colormap(hot) %显示图像cut_1,并使用hot模型彩色化
subplot(2, 2, 3),imshow(cut_2),title('cut_2')
subplot(2, 2, 4),imshow(cut_2),colormap(cool) %显示图像cut_2,并使用cool模型彩色化

% (5)(选做)
% f=imread('lena.jpg');
% g=ice('image',f); %通过ice(交互彩色编辑)函数对图像进行变换
% % ice(交互彩色编辑)函数的参数参照书后面的注释。