#include <iostream>
#include <vector>
#include <string>
#include <unordered_set>

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

int calculateLongestDiffStr(std::string str)
{
    if(str.empty()) return 0;
    if(str.size() == 1) return 1;
    int i = 0, j = 0;
    int max = 1;
    std::unordered_set<char> set1;
    set1.emplace(str[i]);
    for(j = 1; j < str.size(); j++)
    {
        if(set1.find(str[j]) != set1.end())
        {
            while(str[i] != str[j])
            {
                set1.erase(str[i]);
                i++;
            }
            set1.erase(str[i++]);
            set1.emplace(str[j]);
        } else {
            set1.emplace(str[j]);
            if(max < set1.size())
                max = set1.size();
        }
    }
    return max;
}

int main()
{
    string line;
    while(true)
    {
        getline(std::cin, line);
        cout << calculateLongestDiffStr(line);
        break;
    }
    return 0;
}