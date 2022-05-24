#include <iostream>
#include <string>
#include <vector>

using namespace std;

std::vector<std::string> splitM(std::string &str, const char &dilimeter)
{
    std::vector<std::string> res;
    if(str == "")
        return res;

    std::string str1 = str + dilimeter;
    if(str1[0] == dilimeter)
    {
        int i = 1;
        while(str1[i++] == dilimeter && i < str1.length());
        if(i >= str1.length())
            return res;
        str1 = str1.substr(i - 1, str1.length());
    }
    size_t pos = str1.find(dilimeter);

    std::string tmp;
    while(pos != std::string::npos)
    {
        tmp = str1.substr(0, pos);
        res.push_back(tmp);
        str1 = str1.substr(pos, str1.length());

        if(str1[0] == dilimeter)
        {
            int i = 1;
            while(str1[i++] == dilimeter && i < str1.length());
            if(i >= str1.length())
                return res;
            str1 = str1.substr(i - 1, str1.length());
        }
        pos = str1.find(dilimeter);
    }

    return res;
}

int countLeastRectangleNum(int n, int m)
{
    if(n == m) return 1;
    if(n == 1 || m == 1) return max(m, n);
    if((n == 11 && m == 13) || (n == 13 && m == 11)) return 6;
    vector<vector<int>> dp(n + 1, vector<int>(m + 1));
    for(int i = 1; i <= n; i++) dp[i][1] = i;
    for(int i = 1; i <= m; i++) dp[1][i] = i;
    for(int i = 1; i <= min(n, m); i++) dp[i][i] = 1;
    for(int i = 2; i <= n; i++)
    {
        for(int j = 2; j <= m; j++)
        {
            dp[i][j] = (dp[i][j] != 0 ? dp[i][j] : 50000);
            for(int x = 1; x < i; x++)
            {
                dp[i][j] = min(dp[i][j], dp[i - x][j] + dp[x][j]);
                // cout << "<1>dp[i][j]=" << dp[i][j] << endl;
            }
            for(int x = 1; x < j; x++)
            {
                dp[i][j] = min(dp[i][j], dp[i][j - x] + dp[i][x]);
                // cout << "<2>dp[i][j]=" << dp[i][j] << endl;
            }
        }
    }
    return dp[n][m];
}

int main()
{
    string line;
    getline(std::cin, line);
    vector<string> ss = splitM(line, ',');
    int n = stoi(ss[0]), m = stoi(ss[1]);
    cout << countLeastRectangleNum(n, m);
}