#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

#define MAX_SIZE 50001

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

int A[MAX_SIZE], B[MAX_SIZE];
vector<int> nums;

// 理解错了 这个函数是取数值大小连续且下标连续的子数组
int getLongestSuccessiveArr()
{
    int max = nums[0];
    int tmp = nums[0], last = nums[0];
    for(int i = 1; i < nums.size(); i++)
    {
        if(nums[i] - last == 1)
        {
            while(nums[i] - last == 1)
            {
                tmp += nums[i];
                last = nums[i];
                i++;
            }
            if(tmp > max) max = tmp;
        }
        last = nums[i];
        tmp = nums[i];
        if(tmp > max) max = tmp;
    }
    return max;
}

int getBiggestSubArr()
{
    // 暴力
    // if(arr.size() == 0) return 0;
    // int res = arr[0];
    // int length = arr.size();
    // for(int i = 0; i < arr.size(); i++)
    // {
    //     int tmp = arr[i];
    //     int cur = arr[i];
    //     for(int j = i + 1; (j %= length) != i; j++)
    //     {
    //         cur += arr[j];
    //         if(cur > tmp) tmp = cur;
    //     }
    //     if(tmp > res) res = tmp;
    // }
    // return res;

    // 动态规划
    if(nums.size() == 0) return 0;
    int size = nums.size();

    A[0] = nums[0], B[0] = nums[0];
    int max = A[0], start = 0, end = 0;
    for(int i = 1; i < size; i++)
    {
        A[i] = A[i - 1] + nums[i];
        if(A[i] > max)
            max = A[i], start = 0, end = i;
        B[i] = max;
    }
    for(int i = 1; i < size; i++)
    {
        A[size - 1] = A[size - 1] - nums[i - 1];
        if(start == i - 1 && max - nums[start] > max && end != start)
        {
            max = max - nums[start], start++;
        }
        if(A[size - 1] > max)
        {
            max = A[size - 1], start = i, end = i - 1;
        }
        if(A[size - 1] + B[i - 1] > max)
        {
            max = A[size - 1] + B[i - 1], start = i, end = i - 1;
        }
    }

    return max;
}

int main()
{
    string line;
    getline(std::cin, line);
    vector<string> ss = splitM(line, ',');
    for(auto a:ss)
    {
        nums.push_back(stoi(a));
    }
    cout << getBiggestSubArr();
}