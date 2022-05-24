#include <iostream>
#include <string>
#include <vector>
#define MAX_SIZE 50001

using namespace std;

int gambleForNumber(int n)
{
    if(n == 1) return 0;
    vector<vector<int>> dp(n + 1, vector<int>(n + 1));
    for(int j = 2; j <= n; j++)
    {
        for(int i = j - 1; i >= 0; i--)
        {
            dp[i][j] = MAX_SIZE;
            for(int x = i + 1; x <= j - 1; x++)
            {
                dp[i][j] = min(dp[i][j], x + max(dp[i][x - 1], dp[x + 1][j]));
            }
            dp[i][j] = min(dp[i][j], min(i + dp[i + 1][j], j + dp[i][j - 1]));
        }
    }
    return dp[1][n];
}

int main()
{
    int n;
    string line;
    getline(std::cin, line);
    n = stoi(line);
    cout << gambleForNumber(n);
}