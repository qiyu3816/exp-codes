function g = dftfilt(f, H)
% DFTFILT performs frequency domain filtering.
%   G = DFTFILT(F, H) filters F in the frequency domain using the filter
%   transfer function H. The output, G, is the filtered image, which has
%   the same size as F. DFTFILT automatically pads F to be the same size as
%   H. Function PADEDESIZE can be used to determine an appropriate size
%   for H.
%   G = DFTFILT（F，H）使用滤波器传递函数H在频域中对输入图像F滤波。 输出G是滤波后的图像，
%   其大小与F相同。DFTFILT自动将F填充到与H相同的大小 ，PADEDESIZE函数可用于确定H的合适大小。
%
%   DFTFILT assumes that F is real and that H is a real, uncentered,
%   circularly-symmetric filter function.
%   DFTFILT假设F是实数，H是实数，未中心，循环对称的滤波函数。

% Obtain the FFT of the padded input.
% 获取填充之后的FFT变换
F = fft2(f, size(H, 1), size(H, 2));
% Perform filtering
% 滤波
g = real(ifft2(H .* F));
% Crop to orihinal size
% 剪切到原始尺寸
g = g(1 : size(f, 1), 1 : size(f, 2));
