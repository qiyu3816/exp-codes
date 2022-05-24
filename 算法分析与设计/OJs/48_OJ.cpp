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

int CoinsVenture()
{
    if(nums.size() == 0) return 0;
    if(nums.size() == 1) return (nums[0] > 0 ? nums[0] : 0);
    sort(nums.begin(), nums.end());
    int size = nums.size(), positiveI = 0, found = 0;
    for(int i = 0; i < size; i++)
    {
        if(nums[i] >= 0)
        {
            found = 1;
            positiveI = i;
            break;
        }
    }
    int k = (found == 1 ? positiveI : size), m = (found == 1 ? size - positiveI : 0);
    int res = 0;
    if(k == 0)
    {
        for(int i = 0; i < size; i++)
        {
            res += (nums[i] * (i + 1));
        }
        return res;
    } else if(m == 0) {
        return 0;
    }

    int sumOfPositiveBase1 = 0;
    int minusP = 0, positiveP = 0;
    for(int x = 0; x <= k; x++)
    {
        minusP = 0;
        for(int i = k - x; i < k; i++)
        {
            minusP += (nums[i] * (i - k + x + 1));
        }
        // cout << "x=" << x << "minusP=" << minusP << endl;
        for(int j = k; j < size; j++)
        {
            if(x != 0)
            {
                positiveP += sumOfPositiveBase1;
                break;
            }
            positiveP += (nums[j] * (j - k + x + 1));
            if(x == 0) sumOfPositiveBase1 += nums[j];
        }
        // cout << "x=" << x << "positiveP=" << positiveP << endl;
        res = max(minusP + positiveP, res);
    }
    return res;
}

int main()
{
    int n;
    string line;
    getline(std::cin, line);
    vector<string> ss = splitM(line, ' ');
    for(auto s:ss)
    {
        nums.push_back(stoi(s));
    }
    cout << CoinsVenture();
}