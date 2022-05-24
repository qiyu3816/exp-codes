#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

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

int deleteEarn(vector<int>& sum)
{
    vector<int> dp(sum.size(), 0);
    dp[1] = sum[1], dp[2] = max(sum[1], sum[2]);
    int size = sum.size();
    for(int i = 3; i < size; i++)
    {
        dp[i] = max(dp[i - 2] + sum[i], dp[i - 1]);
    }
    return dp[size - 1];
}

int deleteGame()
{
    if(nums.empty()) return 0;
    int maxNum = 0;
    for(auto a:nums)
    {
        if(a > maxNum)
            maxNum = a;
    }
    vector<int> sum(maxNum + 1, 0);
    for(auto num:nums)
    {
        sum[num] += num;
    }
    return deleteEarn(sum);
}

int main()
{
    string line;
    getline(std::cin, line);
    line = line.substr(1, line.length() - 2);
    vector<string> ss = splitM(line, ',');
    for(auto s:ss)
    {
        nums.push_back(stoi(s));
    }
    cout << deleteGame();
}