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

vector<int> nums;

void BestDinnerPath()
{
    int res = 0;
    if(nums.size() < 2) return;
    int size = nums.size();
    int tmp;
    for(int i = 0; i < size; i++)
    {
        for(int j = i + 1; j < size; j++)
        {
            tmp = nums[i] + nums[j] + i -j;
            res = (res < tmp ? tmp : res);
        }
    }
    cout << res;
}

int main()
{
    string line;
    getline(std::cin, line);
    vector<string> ss;
    ss = splitM(line, ',');
    for(int i = 0; i < ss.size(); i++)
    {
        nums.push_back(stoi(ss[i]));
    }
    BestDinnerPath();
}