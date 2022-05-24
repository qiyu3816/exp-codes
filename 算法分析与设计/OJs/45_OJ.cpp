#include <iostream>
#include <string>
#include <vector>
#include <cmath>

using namespace std;

int eggsDropProblem(int k, int n)
{
    vector<int> dp(n + 1);
    // 只有一个鸡蛋的情况 dp[i]代表dp(1, i)
    for(int i = 0; i <= n; i++)
    {
        dp[i] = i;
    }

    // 有j个鸡蛋的情况 dp[i]代表dp[j, i]
    for(int j = 2; j <= k; j++)
    {
        vector<int> tmp(n + 1, 0);
        int x = 1;
        tmp[0] = 0;
        // max(dp[x - 1], dp2[m - x]) >= max(dp[x], dp2[m - x - 1])
        // max(T1(x - 1), T2(x - 1)) >= max(T1(x), T2(x)).
        for(int m = 1; m <= n; m++)
        {
            // 满足交点的x的值只会递增 所以每次直接从上一次的交点开始遍历
            while(x < m && max(dp[x - 1], tmp[m - x]) >= max(dp[x], tmp[m - x - 1]))
            {
                x++;
            }
            tmp[m] = 1 + max(dp[x - 1], tmp[m - x]);
        }
        dp = tmp; // 更新dp
    }
    return dp[n];
}

int main()
{
    int n;
    string line;
    getline(std::cin, line);
    n = stoi(line);
    cout << eggsDropProblem(2, n);
}