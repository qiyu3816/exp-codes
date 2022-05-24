f=imread('number.tiff');
F=fft2(f); %��ͼ����и���Ҷ�任
%�Ա任��ͼ����ж����仯������������ƽ�ƣ�ʹ�����Ļ�
S=fftshift(log(1+abs(F)));
S=gscale(S, 'full8', 0, 255); %��Ƶ��ͼ������0-256�ķ�Χ��
figure(),imshow(S) %��ʾƵ��ͼ��

%h=fspecial('average', 10); 
h=fspecial('sobel'); %�����ռ䡮sobel��ģ��
figure,freqz2(h) %�鿴��ӦƵ���˲�����ͼ��
PQ=paddedsize(size(f)); %�����˲�ʱ�����С�ľ���
H=freqz2(h,PQ(1),PQ(2)); %����Ƶ���еġ�sobel���˲���
H1=ifftshift(H); %�����������У�ʹ��ԭ��λ��Ƶ�ʾ�������Ͻ�
figure,imshow(abs(H),[]) %��ͼ����ʽ��ʾ�˲���
figure,imshow(abs(H1),[])

gs=imfilter(double(f),h); %��ģ��h���п����˲�
gf=dftfilt(f,H1); %���˲�����ͼ����е�ͨ�˲�
figure,imshow(gs,[])
figure,imshow(gf,[])
figure,imshow(abs(gs),[])
figure,imshow(abs(gf),[])

f=imread('number.tiff'); %��ȡͼƬ
PQ=paddedsize(size(f)); %�����˲�ʱ�����С�ľ���
D0=0.05*PQ(1); %�趨��˹��ͨ�˲�������ֵ
H=hpfilter('gaussian',PQ(1),PQ(2),D0); %������˹��ͨ�˲���
g=dftfilt(f,H); %��ͼ������˲�
figure,imshow(f) %��ʾԭͼ��
figure,imshow(g,[]) %��ʾ�˲���ͼ��