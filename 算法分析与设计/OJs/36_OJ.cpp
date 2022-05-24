#include <iostream>
#include <string>
#define MAX_SIZE 2001

using namespace std;

int getXthUglyNumber(int x)
{
    int dp[MAX_SIZE];
    dp[1] = 1;
    int p2 = 1, p3 = 1, p5 = 1;
    for(int i = 2; i <= x; i++)
    {
        int next2 = dp[p2] * 2, next3 = dp[p3] * 3, next5 = dp[p5] * 5;
        dp[i] = min(min(next2, next3), next5);
        // p2 p3 p5必定处于小于i的位置 如果其下一任丑数与下一任最小丑数相等
        // 则指针加一指向下一个基础丑数
        if(dp[i] == next2)
        {
            p2++;
        }
        if(dp[i] == next3)
        {
            p3++;
        }
        if(dp[i] == next5)
        {
            p5++;
        }
    }
    return dp[x];
}

int main()
{
    int x;
    string line;
    getline(std::cin, line);
    x = stoi(line);
    cout << getXthUglyNumber(x);
}