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

vector<int> nums;

int leastDeflection()
{
    int p_max = 1;
    for(int a:nums)
    {
        while(a % 2 == 0) a /= 2;
        p_max = max(p_max, a); // 奇数形态最大值
    }
    vector<int> upper;
    int min = p_max;
    for(int a : nums)
    {
        if(a % 2 == 1) a *= 2; // 奇数小于p_max则乘二存入upper 等于p_max直接存入
        while(a >= 2 * p_max) a /= 2; // 偶数大于等于p_max的循环除二直到小于2*p_max后存入
        if(a >= p_max) upper.push_back(a);
        min = std::min(min, a);
    }
    sort(upper.begin(), upper.end());
    int ans = upper.back() - min;
    for(int i = upper.size() - 1; upper[i] > p_max; i -= 1)
    {
        min = std::min(min, upper[i] / 2);
        ans = std::min(ans, upper[i - 1] - min);
    }
    return ans;
}

int main()
{
    string line;
    getline(std::cin, line);
    vector<string> ss = splitM(line, ',');
    for(auto s:ss)
    {
        nums.push_back(stoi(s));
    }
    cout << leastDeflection();
}