#include <iostream>
#include <string>
#include <vector>
#include <cmath>
#define MY_MOD 1000000007

using namespace std;

long long countGoodNumber(long long n)
{
    if(n == 0) return 0;
    long long a = n / 2 + n % 2, b = n / 2;
    long long res = 1;
    for(int i = 0; i < a; i++)
    {
        res *= 5;
        res %= MY_MOD;
    }
    for(int i = 0; i < b; i++)
    {
        res *= 4;
        res %= MY_MOD;
    }
    return res;
}

int main()
{
    string line;
    getline(std::cin, line);
    long long n = stoll(line);
    cout << countGoodNumber(n);
}