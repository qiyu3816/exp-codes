I = imread('v1_red.jpg');
gray = rgb2gray(I);
imwrite(gray, 'infer_near.jpg');