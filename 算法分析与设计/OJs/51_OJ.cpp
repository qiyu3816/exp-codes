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

int bestBook()
{
    if(nums.empty()) return 0;
    if(nums.size() == 1) return nums[0];
    int size = nums.size();
    vector<int> dp(size, 0);
    dp[0] = nums[0];
    dp[1] = max(nums[0], nums[1]);
    for(int i = 2; i < size; i++)
    {
        dp[i] = max(nums[i] + dp[i - 2], dp[i - 1]);
    }
    return dp[size - 1];
}

int main()
{
    string line;
    getline(std::cin, line);
    vector<string> ss = splitM(line, ',');
    for(auto s:ss)
    {
        nums.push_back(stoi(s));
    }
    cout << bestBook();
}