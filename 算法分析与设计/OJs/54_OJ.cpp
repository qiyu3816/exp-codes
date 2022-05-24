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

bool comp(const std::pair<int, int> p1, const std::pair<int, int> p2)
{
    return (p1.first == p2.first ? p1.second < p2.second : p1.first < p2.first);
}

vector<pair<int, int>> goods;

void mostSatisfication(int c, int n)
{
    if(goods.empty())
    {
        cout << 0;
        return;
    }
    if(goods[0].first > c)
    {
        cout << 0;
        return;
    }
    sort(goods.begin(), goods.end(), comp);
    vector<vector<int>> dp(n + 1, vector<int>(c + 1));
    int size = goods.size();
    for(int i = 0; i < size && goods[i].first <= c; i++)
    {
        dp[i + 1][goods[i].first] = goods[i].second;
        if(i == 0)
        {
            for(int j = goods[i].first; j <= c; j++)
                dp[i + 1][j] = goods[i].second;
        }
    }

    // for(int i = 0; i <= n; i++)
    // {
    //     for(int j = 0; j <= c; j++)
    //     {
    //         cout << dp[i][j] << " ";
    //     }
    //     cout << endl;
    // }
    // cout << endl;

    for(int i = 2; i <= n; i++)
    {
        for(int j = 2; j <= c; j++)
        {
            int take = (j - goods[i - 1].first >= 0 ? (dp[i - 1][j - goods[i - 1].first] + goods[i - 1].second) : 0);
            int give = dp[i - 1][j];
            dp[i][j] = max(dp[i][j], max(take, give));
        }
        // cout << "i=" << i << endl;
        // for(int k = 0; k <= n; k++)
        // {
        //     for(int p = 0; p <= c; p++)
        //     {
        //         cout << dp[k][p] << " ";
        //     }
        //     cout << endl;
        // }
        // cout << endl;
    }
    cout << dp[n][c];
}

int main()
{
    string line;
    getline(std::cin, line);
    vector<string> ss = splitM(line, ' ');
    int c = stoi(ss[0]), n = stoi(ss[1]);
    while(getline(std::cin, line))
    {
        ss = splitM(line, ' ');
        int cost = stoi(ss[0]), num = stoi(ss[1]), satisfication = stoi(ss[2]);
        n += (num - 1);
        for(int j = 0; j < num; j++)
        {
            pair<int, int> p;
            p.first = cost, p.second = satisfication;
            goods.push_back(p);
        }
    }
    mostSatisfication(c, n);
}