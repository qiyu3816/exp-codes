#include <iostream>
#include <vector>

using namespace std;

int n;
vector<int> nums;

int mostSumOfSubArray()
{
    if(nums.empty()) return 0;
    int last = 0, res = nums[0];
    for(auto x:nums)
    {
        last = max(last + x, x); // 和当前last保存的子串和进行比较
        res = max(res, last);
    }
    return res;
}

int main()
{
    cin >> n;
    nums.resize(n);
    int size = n;
    while(size--)
    {
        cin >> nums[n - size - 1];
    }
    cout << mostSumOfSubArray();
}