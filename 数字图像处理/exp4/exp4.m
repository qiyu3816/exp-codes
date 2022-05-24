% (1)
rgb_image=imread('flower.tiff'); %��ȡͼ��flower1.tif
fR=rgb_image(:,:,1); %��ȡͼ��ĺ�ɫ����
fG=rgb_image(:,:,2); %��ȡͼ�����ɫ����
fB=rgb_image(:,:,3); %��ȡͼ�����ɫ����
imwrite(fR, 'v1_red.jpg');
imwrite(fG, 'v1_green.jpg');
imwrite(fB, 'v1_blue.jpg');
figure(1)
subplot(1, 3, 1),imshow(fR) %�ֱ���ʾͼ��
subplot(1, 3, 2),imshow(fG)
subplot(1, 3, 3),imshow(fB)

% (2)
yiq_image=rgb2ntsc(rgb_image);
fY=yiq_image(:,:,1); %ͼ��flower1.tif������
fI=yiq_image(:,:,2); %ͼ��flower1.tif��ɫ��
fQ=yiq_image(:,:,3); %ͼ��flower1.tif�ı��Ͷ�
figure(2),
subplot(1, 3, 1), imhist(fR), title('����ǰR')
subplot(1, 3, 2), imhist(fG), title('����ǰG')
subplot(1, 3, 3), imhist(fB), title('����ǰB')
figure(3),
subplot(1, 3, 1), imshow(fY), title('����ǰ����')
subplot(1, 3, 2), imshow(fI), title('����ǰɫ��')
subplot(1, 3, 3), imshow(fQ), title('����ǰ���Ͷ�')
fR=histeq(fR,256); %�Բ�ɫͼ��ķ�������ֱ��ͼ���⻯
fG=histeq(fG,256);
fB=histeq(fB,256);
RGB_image=cat(3,fR,fG,fB); %��ֱ��ͼ���⻯��Ĳ�ɫͼ��ϲ�
YIQ_image=rgb2ntsc(RGB_image);
fY=YIQ_image(:,:,1); %������ͼ��flower1.tif������
fI=YIQ_image(:,:,2); %������ͼ��flower1.tif��ɫ��
fQ=YIQ_image(:,:,3); %������ͼ��flower1.tif�ı��Ͷ�
figure(4),
subplot(1, 3, 1), imhist(fR), title('�����R')
subplot(1, 3, 2), imhist(fG), title('�����G')
subplot(1, 3, 3), imhist(fB), title('�����B')
figure(5),
subplot(1, 3, 1), imshow(fY), title('���������')
subplot(1, 3, 2), imshow(fI), title('�����ɫ��')
subplot(1, 3, 3), imshow(fQ), title('����󱥺Ͷ�')
figure(6),imshow(RGB_image),title('�����Ĳ�ɫͼ��') %�۲촦���Ĳ�ɫͼɫ�ȣ����Ȳ���ǰ��

% (3)
% f1=imread('v1_red.jpg');
% f2=imread('v1_green.jpg');
% f3=imread('v1_blue.jpg');
% f4=imread('infer_near.jpg'); % ����ͼ�񣡣���
% ture_color=cat(3,f1,f2,f3);
% figure,imshow(ture_color) %��ʾ�ɺ졢�̡�������ͼ�ϳɵĲ�ɫͼ
% false_color=cat(3,f4,f2,f3); %�ý�����ͼ�����R����
% figure,imshow(false_color) %��ʾ�ɽ����⡢�̡�������ͼ�ϳɵļٲ�ɫͼ

% (4)
f=imread('lena.jpg');
cut_1=imadjust(f,[0.0925 0.5],[0.0925 0.5]);%��ȡ�Ҷ���16-128֮�������
cut_2=imadjust(f,[0.5 1],[0.5 1]); %��ȡ�Ҷ���128-256֮�������
figure(7)
subplot(2, 2, 1),imshow(cut_1),title('cut_1')
subplot(2, 2, 2),imshow(cut_1),colormap(hot) %��ʾͼ��cut_1,��ʹ��hotģ�Ͳ�ɫ��
subplot(2, 2, 3),imshow(cut_2),title('cut_2')
subplot(2, 2, 4),imshow(cut_2),colormap(cool) %��ʾͼ��cut_2,��ʹ��coolģ�Ͳ�ɫ��

% (5)(ѡ��)
% f=imread('lena.jpg');
% g=ice('image',f); %ͨ��ice(������ɫ�༭)������ͼ����б任
% % ice(������ɫ�༭)�����Ĳ�������������ע�͡�