function PQ = paddedsize(AB, CD, PARAM)
% 计算填充尺寸以供基于FFT的滤波器
% PQ = PADDEDSIZE(AB),AB = [A B], PQ = 2 * AB
%
% PQ = PADDEDSIZE(AB, 'PWR2')， PQ（1） = PQ（2） = 2 ^ nextpow2(2 * m), m =
% MAX(AB).
% 
% PQ = PADDEDSIZE(AB, CD)，AB = [A B], CD = [C D]
%
%  PQ = PADDEDSIZE(AB, CD, 'PWR2')， PQ（1） = PQ（2） = 2 ^ nextpow2(2 * m), m =
% MAX([AB CD]).

if nargin == 1
    PQ = 2 * AB;
elseif nargin == 2 & ~ischar(CD)
    PQ = AB + CD -1;
    PQ = 2 * ceil(PQ / 2);  % ceil（N）返回比N大的最小整数，为了避免出现奇数，因为处理偶数数组快
elseif nargin == 2
    m = max(AB);
    P = 2 ^ nextpow2(2 * m);  % nextpow2（N）返回第一个P，使得2. ^ P> = abs（N）。 
    % 对于FFT运算，找到最接近两个序列长度的2 的幂次方通常很有用。
    PQ = [P, P];
elseif nargin == 3
    m = max([AB CD]);
    P = 2 ^ nextpow2(2 * m);
    PQ = [P, P];
else
    error('Wrong number of input')
end
