#include <iostream>
#include <string>
#include <vector>
#define MAX_SIZE 1000

using namespace std;

int dp[MAX_SIZE][MAX_SIZE];

void leastTransfer()
{
    string str1, str2;
    cin >> str1 >> str2;
    int size1 = str1.length(), size2 = str2.length();
    // dp[i][j] 表示str1的前i到str2的前j的最短变化次数
    for(int i = 1; i <= size1; ++i)
        dp[i][0] = i;
    for(int i = 1; i <= size2; ++i)
        dp[0][i] = i;
    for(int i = 1; i <= size1; ++i)
    {
        for (int j = 1; j <= size2; ++j)
        {
            if (str1[i - 1] == str2[j - 1])
                dp[i][j] = dp[i - 1][j - 1];
            else {
                dp[i][j] = min(dp[i - 1][j], min(dp[i][j - 1], dp[i - 1][j - 1])) + 1;
            }
        }
    }
    cout << dp[size1][size2] << endl;
}

int main()
{
    leastTransfer();
}