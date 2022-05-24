#include <iostream>
#include <string>
#include <vector>
#include <cstring>

using namespace std;

string s, p;

int ifFitable()
{
    int length1 = s.length(), length2 = p.length();
    int dp[length1 + 1][length2 + 1];
    memset(dp, 0, sizeof(dp));
    
    // 初始化
    dp[0][0] = 1;
    for(int j = 1; j <= length2; j++)
    {
        if(p[j - 1] == '*')
        {
            dp[0][j] = 1;
        } else {
            break;
        }
    }

    // 处理
    for(int i = 1; i <= length1; i++)
    {
        for(int j = 1; j <= length2; j++)
        {
            if(p[j - 1] == '?' || p[j - 1] == s[i - 1])
            {
                dp[i][j] = dp[i - 1][j - 1];
            } else if(p[j - 1] == '*') {
                dp[i][j] = dp[i - 1][j] || dp[i][j - 1];
            }
        }
    }
    return dp[length1][length2];
}

int main()
{
    getline(std::cin, s);
    getline(std::cin, p);
    cout << ifFitable();
}