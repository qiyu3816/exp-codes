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

int getLongestSubStrWithKApperances(string& s, int l, int r, int k)
{
    // 初始化计数数组
    vector<int> count(26, 0);
    for (int i = l; i <= r; i++)
    {
        count[s[i] - 'a']++;
    }

    // 找到下一个出现了但出现次数小于k的字符
    char split = 0;
    for (int i = 0; i < 26; i++)
    {
        if (count[i] > 0 && count[i] < k)
        {
            split = i + 'a';
            break;
        }
    }

    // 每个字符出现次数大于等于k 不需要切分了
    if (split == 0)
    {
        return r - l + 1;
    }

    int i = l;
    int res = 0;
    while (i <= r)
    {
        while (i <= r && s[i] == split)
        {
            i++;
        }
        if (i > r)
        {
            break;
        }
        int newLeft = i;
        while (i <= r && s[i] != split)
        {
            i++;
        }
        int length = getLongestSubStrWithKApperances(s, newLeft, i - 1, k);
        res = max(res, length);
    }
    return res;
}

int main()
{
    string line, num;
    getline(std::cin, line);
    line = line.substr(1, line.length() - 2);
    getline(std::cin, num);
    int k = stoi(num);
    cout << getLongestSubStrWithKApperances(line, 0, line.length() - 1, k);
}