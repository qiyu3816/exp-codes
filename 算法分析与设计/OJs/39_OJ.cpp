#include <iostream>
#include <string>
#include <vector>
#define MY_MOD 1000'000'007

using namespace std;

int walkOutFromGrid(int m, int n, int maxMove, int startRow, int startColumn)
{
    vector<vector<int>> directions = {{1, 0}, {0, 1}, {-1, 0}, {0, -1}};
    vector<vector<int>> dp(m, vector<int>(n));
    dp[startRow][startColumn] = 1; // dp[i][j] 代表当前步骤从初始点到达此地的路径数

    int res = 0;
    for(int i = 0; i < maxMove; i++)
    {
        vector<vector<int>> tmp(m, vector<int>(n));
        for(int j = 0; j < m; j++)
        {
            for(int k = 0; k < n; k++)
            {
                int count = dp[j][k];
                if(count > 0)
                {
                    for(auto& direction:directions)
                    {
                        int j1 = j + direction[0], k1 = k + direction[1];
                        if(j1 >= 0 && j1 < m && k1 >= 0 && k1 < n)
                        {
                            tmp[j1][k1] = (tmp[j1][k1] + count) % MY_MOD;
                        } else {
                            res = (res + count) % MY_MOD;
                        }
                    }
                }
            }
        }
        dp = tmp;
    }
    return res;
}

int main()
{
     int m, n, maxMove, startRow, startColumn;
     string line;
     getline(std::cin, line);
     m = stoi(line);
     getline(std::cin, line);
     n = stoi(line);
     getline(std::cin, line);
     maxMove = stoi(line);
     getline(std::cin, line);
     startRow = stoi(line);
     getline(std::cin, line);
     startColumn = stoi(line);
     cout << walkOutFromGrid(m, n, maxMove, startRow, startColumn);
}