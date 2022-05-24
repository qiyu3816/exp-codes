#include <iostream>
#include <string>
#include <cstring>
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

void TypesToPickGoods(int x, int m)
{
    if(nums.empty())
    {
        cout << "-1";
        return;
    }
    sort(nums.begin(), nums.end());
    if(nums[0] > x)
    {
        cout << "-1";
        return;
    }
    int dp[m + 1][x + 1];
    int size = nums.size();
    memset(dp, 0, sizeof(dp));
    
    for(int i = 1; i <= m; i++)
    {
        if(nums[i - 1] <= x)
            dp[i][nums[i - 1]] = 1;
    }
    
    // for(int i = 0; i <= m; i++)
    // {
    //     for(int j = 0; j <= x; j++)
    //     {
    //         cout << dp[i][j] << " ";
    //     }
    //     cout << endl;
    // }
    // cout << endl;

    for(int i = 2; i <= m; i++)
    {
        for(int j = 1; j <= x; j++)
        {
            int take = ((j - nums[i - 1] >= 0) ? dp[i - 1][j - nums[i - 1]] : 0);
            int give = dp[i - 1][j];
            dp[i][j] += take + give;
        }
        // cout << "i=" << i << endl;
        // for(int k = 0; k <= m; k++)
        // {
        //     for(int p = 0; p <= x; p++)
        //     {
        //         cout << dp[k][p] << " ";
        //     }
        //     cout << endl;
        // }
        // cout << endl;
    }
    if(dp[m][x] == 0)
    {
        cout << "-1";
    } else {
        cout << dp[m][x];
    }
}

int main()
{
    string line;
    getline(std::cin, line);
    vector<string> ss = splitM(line, ' ');
    int x = stoi(ss[0]), m = stoi(ss[1]);
    getline(std::cin, line);
    ss = splitM(line, ' ');
    for(auto s:ss)
    {
        nums.push_back(stoi(s));
    }
    TypesToPickGoods(x, m);
}