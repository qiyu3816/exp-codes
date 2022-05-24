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

static bool comp(const std::pair<int, int> p1, const std::pair<int, int> p2)
{
    return (p1.first == p2.first ? p1.second < p2.second : p1.first < p2.first);
}

vector<pair<int, int>> temperaturesP;
int n;

void observeTemprature()
{
    if(n == 1)
    {
        cout << 0;
        return;
    }
    sort(temperaturesP.begin(), temperaturesP.end(), comp);

    vector<int> res(n);
    for(int i = 0; i < n; i++)
    {
        int find = 0;
        for(int j = i + 1; j < n; j++)
        {
            if(temperaturesP[j].second > temperaturesP[i].second && temperaturesP[j].first > temperaturesP[i].first)
            {
                if(find == 0)
                    res[temperaturesP[i].second] = n;
                res[temperaturesP[i].second] = min(res[temperaturesP[i].second], temperaturesP[j].second - temperaturesP[i].second);
                find = 1;
            }
        }
        if(find == 0)
            res[temperaturesP[i].second] = 0;
    }

    for (int i = 0; i < n; i++)
    {
        cout << res[i] << ", "[i == (n - 1)];
    }
}

int main()
{
    string line;
    getline(std::cin, line);
    vector<string> ss = splitM(line, ',');
    n = ss.size();
    temperaturesP.resize(n);
    for (int i = 0; i < n; i++)
    {
        pair<int, int> p;
        p.first = stoi(ss[i]);
        p.second = i;
        temperaturesP[i] = p;
    }
    observeTemprature();
}