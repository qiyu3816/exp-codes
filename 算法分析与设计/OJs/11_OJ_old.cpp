#include <iostream>

using namespace std;

long long getFactorial(long long n)
{
    if(n == 0) return 1;
    return n * getFactorial(n - 1);
}

long long getCandyDividionTypes(long long n)
{
    if (n == 0) return 1;
    long long res = 0;
    if(n % 2 == 0)
    {
        long long a = n / 2;
        long long b = a;
        for(; b >= 0; b--, a++)
        {
            res += (getFactorial(a) / getFactorial(b) / getFactorial(a - b));
        }
    } else {
        long long a = n / 2 + 1;
        long long b = n / 2;
        for(; b >= 0; b--, a++)
        {
            res += (getFactorial(a) / getFactorial(b) / getFactorial(a - b));
        }
    }
    return res;
}

int main()
{
    long long n;
    cin >> n;
    cout << getCandyDividionTypes(n);
}