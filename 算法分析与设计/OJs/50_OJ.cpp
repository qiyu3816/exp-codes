#include <iostream>
#include <string>
#include <vector>
#include <cstring>

using namespace std;

// 不能处理过大的输入 正确做法可以用01字典树
int countNumsWithoutAdjust1InBin(int n)
{
    if(n == 0) return 1;
    if(n == 1) return 2;
    // 为1表示i含有连续1
    int dp[n + 1];
    dp[0] = 0, dp[1] = 0, dp[2] = 0;
    int sum[n + 1];
    sum[0] = 1, sum[1] = 2, sum[2] = 3;
    for(int i = 3; i <= n; i++)
    {
        if(i % 2 == 0)
        {
            dp[i] = dp[i / 2];
            sum[i] = sum[i - 1] + (dp[i] == 1 ? 0 : 1);
        } else {
            int index = i;
            int sign = 1, type = 0;
            while(index = (index >> 1))
            {
                if(sign == 1 && index & 1 == sign)
                {
                    dp[i] = 1, type = 1;
                    sum[i] = sum[i - 1];
                    break;
                }
                sign = index & 1;
            }
            if(type == 0)
            {
                dp[i] = 0;
                sum[i] = sum[i - 1] + 1;
            }
        }
    }
    return sum[n];
}

int main()
{
    string line;
    getline(std::cin, line);
    int n = stoi(line);
    cout << countNumsWithoutAdjust1InBin(n);
}