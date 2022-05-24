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

int EqualityTypes(int l, int r, int target)
{
    if(nums.empty()) return 0;
    if(l == r)
    {
        int res = 0;
        if(nums[l] == target) res++;
        if(nums[l] == -target) res++;
        return res;
    }
    int size = nums.size();
    int sign1 = nums[l], sign2 = -nums[l];
    int target1 = target - sign1, target2 = target - sign2;
    int types = 0;
    return types + EqualityTypes(l + 1, r, target1) + EqualityTypes(l + 1, r, target2);
}

int main()
{
    string line;
    getline(std::cin, line);
    vector<string> ss = splitM(line, ',');
    getline(std::cin, line);
    int target = stoi(line);
    for(auto s:ss)
    {
        nums.push_back(stoi(s));
    }
    cout << EqualityTypes(0, ss.size() - 1, target);
}