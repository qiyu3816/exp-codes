#include <iostream>
#include <vector>
#include <numeric>

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

int n;
vector<int> nums;

// 背包问题做法
void ifCanDivideInto2EqualSubArr()
{
    if(nums.empty())
    {
        cout << "false";
        return;
    }
    int sum = accumulate(nums.begin(), nums.end(), 0);
    if(sum % 2 != 0)
    {
        cout << "false";
        return;
    }
    int target = sum / 2;
    vector<int> dp(target + 1);
    dp[0] = true;
    for(int weight:nums) // 逐个遍历决定是否取
    {
        for(int j = target; j >= weight; j--)
        {
            dp[j] = (dp[j] || dp[j - weight]);
        }
    }

    cout << (dp[target] == 0 ? "false" : "true");
}

int main()
{
    string line;
    getline(std::cin, line);
    vector<string> ss = splitM(line, ',');
    n = ss.size();
    nums.resize(n);
    for(int i = 0; i < n; i++)
    {
        nums[i] = stoi(ss[i]);
    }
    ifCanDivideInto2EqualSubArr();
}