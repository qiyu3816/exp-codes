#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
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

vector<int> matchsticks;

// index 当前火柴位置
// length 目标边长
// edges 当前边长
bool backtrack(vector<int>& nums, int index, int length, vector<int> edges) {
    if(index == -1) // 火柴都访问完了
    {
        if (edges[0] == edges[1] && edges[1] == edges[2] && edges[2] == edges[3])
            return true;
        return false;
    }

    for(int i = 0; i < edges.size(); i++)
    {
        // 火柴加入edges[i]超长或等于上一边(上一边如果正确 就已经return了 所以肯定失败了)则跳过
        if(edges[i] + nums[index] > length || (i > 0 && edges[i] == edges[i - 1]))
            continue;

        edges[i] += nums[index];
        // next
        if(backtrack(nums, index - 1, length, edges))
            return true;
        edges[i] -= nums[index];
    }
    //如果不能构成正方形，直接返回false
    return false;
}

bool ifAble2CreateRect()
{
    int sum = 0;
    for(int num : matchsticks)
    {
        sum += num;
    }
    if(sum == 0 || (sum & 3) != 0 || matchsticks.size() < 4)
        return false;

    sort(matchsticks.begin(), matchsticks.end());
    vector<int> edges(4, 0);
    // 从大的开始
    return backtrack(matchsticks, matchsticks.size() - 1, sum >> 2, edges);
}

int main()
{
    string line;
    getline(std::cin, line);
    line = line.substr(1, line.length() - 2);
    vector<string> ss = splitM(line, ',');
    for(auto s:ss)
    {
        matchsticks.push_back(stoi(s));
    }
    cout << (ifAble2CreateRect() ? "true" : "false");
}