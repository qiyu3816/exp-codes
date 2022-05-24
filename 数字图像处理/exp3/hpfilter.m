function H = hpfilter(type, M, N, D0, n)
% LPFILTER Computes frequency domain highpass filters
%   H = HPFILTER(TYPE, M, N, D0, n) creates the transfer function of a
%   highpass filter, H, of the specified TYPE and size (M-by-N). To view the
%   filter as an image or mesh plot, it should be centered using H =
%   fftshift(H)
%   Valid value for TYPE, D0, and n are:
%   'ideal' Ideal highpass filter with cutoff frequency D0. n need not be
%           supplied. D0 must be positive.
%   'btw'   Butterworth highpass filter of order n, and cutoff D0. The
%           default value for n is 1.0. D0 must be positive.
%   'gaussian'Gaussian highpass filter with cutoff (standard deviation) D0.
%           n need not be supplied. D0 must be positive.
% The transfer function Hhp of highpass filter is 1 - Hlp, where Hlp is the
% transfer function of the corresponding lowpass filter. Thus, we can use
% function lpfilter to generate highpass filters.
%
% 计算给定类型（理想、巴特沃兹、高斯）的频域高通滤波器

% Use function dftuv to set up the meshgrid arrays needed for computing the
% required distances.
if nargin == 4
    n = 1;
end
Hlp = lpfilter(type, M, N, D0, n);
H = 1 - Hlp;      
