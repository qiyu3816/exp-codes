#include <iostream>
#include <vector>
#include <numeric>

using namespace std;

int n;
vector<int> nums;

// 背包问题做法
int leastDiffOfSumOf2SubArr()
{
    if(nums.empty()) return 0;
    int sum = accumulate(nums.begin(), nums.end(), 0);
    int target = sum / 2;
    vector<int> dp(target + 1);
    dp[0] = true;
    for(int weight:nums) // 逐个遍历决定是否取
    {
        for(int j = target; j >= weight; j--)
        {
            dp[j] = (dp[j] || dp[j - weight]);
        }
    }

    for(int j = target;; j--)
    {
        if(dp[j])
            return sum - 2 * j;
    }
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
    cout << leastDiffOfSumOf2SubArr();
}