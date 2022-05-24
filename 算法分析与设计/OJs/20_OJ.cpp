#include <iostream>
#include <vector>
#include <string>
#include <cstring>
#include <unordered_map>

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

int countMostAppearedNum(vector<string> &ss)
{
    if(ss.empty()) return 0;
    if(ss.size() == 1) return stoi(ss[0]);
    unordered_map<int, int> A;
    int res = 0, max = 0;
    for(int i = 0; i < ss.size(); i++)
    {
        int tmp = stoi(ss[i]);
        if(A.find(tmp) != A.end())
        {
            A[tmp]++;
        } else {
            A.emplace(tmp, 1);
        }
        res = max < A[tmp] ? tmp : res;
        max = max < A[tmp] ? A[tmp] : max;
    }
    return res;
}

int main()
{
    string line;
    vector<string> ss;
    getline(std::cin, line);
    line = line.substr(1, line.length() -2);
    ss = splitM(line, ',');
    cout << countMostAppearedNum(ss);
}