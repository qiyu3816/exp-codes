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

vector<int> cost;

int getLeastPassCost()
{
    if(cost.empty()) return 0;
    if(cost.size() == 1) return cost[0];
    int size = cost.size();
    vector<int> dp(size, 0);
    dp[0] = cost[0];
    dp[1] = cost[1];
    for(int i = 2; i < size; i++)
    {
        dp[i] = min(dp[i - 1] + cost[i], dp[i - 2] + cost[i]);
    }
    return min(dp[size - 1], dp[size - 2]);
}

int main()
{
    string line;
    getline(std::cin, line);
    vector<string> ss = splitM(line, ' ');
    for(auto s:ss)
    {
        cost.push_back(stoi(s));
    }
    cout << getLeastPassCost();
}