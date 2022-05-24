#include <iostream>
#include <string>

using namespace std;

long long spec = 7; // 数的是2的出现次数 这样2及以下不会进位 3及以上会进位

long long count2Appearances(long long n)
{
    if(n <= 1) return 0;
    if(n <= 11) return 1;
    long long a = 0, b = 0, res = 0;
    for(long long i = 1; i <= n; i *= 10)
    {
        a = n / i;
        b = n % i;
        res += (a + spec) / 10 * i + (a % 10 == 2) * (b + 1);
    }
    return res;
}

int main()
{
    string line;
    getline(std::cin, line);
    long long n = stoll(line);
    cout << count2Appearances(n);
}