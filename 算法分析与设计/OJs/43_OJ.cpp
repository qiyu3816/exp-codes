#include <iostream>
#include <string>
#include <vector>
#include <cstring>

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

vector<int> nums;

int whoWins()
{
    int size = nums.size();
    if(size <= 2) return 1;
    int dp[size][size]; // dp[i][j]表示数组nums[i]~nums[j]段两者获得分数的最大差
    memset(dp, 0, sizeof(dp));
    for(int i = 0; i < size; i++)
    {
        dp[i][i] = nums[i];
    }
    for(int i = size - 2; i >= 0; i--)
    {
        for(int j = i + 1; j < size; j++)
        {
            dp[i][j] = max(nums[i] - dp[i + 1][j], nums[j] - dp[i][j - 1]);
        }
    }
    return (dp[0][size - 1] >= 0);
}

int main()
{
    string line;
    getline(std::cin, line);
    vector<string> ss = splitM(line, ' ');
    for(auto s:ss)
    {
        nums.push_back(stoi(s));
    }
    cout << (whoWins() ? "true" : "false");
}