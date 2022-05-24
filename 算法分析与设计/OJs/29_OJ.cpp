// 涉及一些有用的STL容器用法
#include <iostream>
#include <string>
#include <vector>
#include <utility>
#include <queue>
#include <unordered_map>
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

int k;
vector<string> ss;
vector<int> nums;

static bool cmp(pair<int, int>& m, pair<int, int>& n)
{
    return m.second > n.second;
}

void countKthMostAppeared()
{
    unordered_map<int, int> u_map;
    for(auto& v : nums)
    {
        u_map[v]++;
    }

    priority_queue<pair<int, int>, vector<pair<int, int>>, decltype(&cmp)> q(cmp);
    for(auto p:u_map)
    {
        if(q.size() == k)
        {
            if(q.top().second < p.second)
            {
                q.pop();
                q.emplace(p.first, p.second);
            }
        } else {
            q.emplace(p.first, p.second);
        }
    }
    vector<int> ret;
    while(!q.empty())
    {
        ret.emplace_back(q.top().first);
        q.pop();
    }

    // 对应数字按从小到大输出
    sort(ret.begin(), ret.end());
    for(int i = 0; i < ret.size(); i++)
    {
        if(i == ret.size() - 1)
        {
            cout << ret[i];
            break;
        }
        cout << ret[i] << ",";
    }
}

int main()
{
    string line;
    getline(std::cin, line);
    ss = splitM(line, ',');
    getline(std::cin, line);
    k = stoi(line);
    for(auto s:ss)
    {
        nums.push_back(stoi(s));
    }
    countKthMostAppeared();
}