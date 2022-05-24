// 力扣过了 OJ给我WA了 不晓得为啥
#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

vector<int> nums;

// 判断v是否是完全平方数
bool ifCompleteSquare(int v)
{
    int sq = int(std::sqrt(v) + 0.5);
    return sq * sq == v;
}

int CountAdjastNumsSquareArrs(int last, int n)
{
    if(n == 0 && last == -1) return 0;
    if(n == 0 && last != -1) return 1;
    int res = 0, lastChecked; // lastChecked把已经用过的数跳过
    for(int i = 0; i < n; i++)
    {
        if(lastChecked == nums[i])
            continue;
        lastChecked = nums[i];
        if(last == -1)
        {
            int curLast = nums[i];
            nums.erase(nums.begin() + i);
            res += CountAdjastNumsSquareArrs(curLast, n - 1);
            nums.insert(nums.begin() + i, curLast);
        } else if(ifCompleteSquare(last + nums[i])) {
            int curLast = nums[i];
            nums.erase(nums.begin() + i);
            res += CountAdjastNumsSquareArrs(curLast, n - 1);
            nums.insert(nums.begin() + i, curLast);
        }
    }
    return res;
}

int main()
{
    int n;
    cin >> n;
    nums.resize(n);
    for (int i = 0; i < n; i++)
    {
        cin >> nums[i];
    }
    sort(nums.begin(), nums.end());
    cout << CountAdjastNumsSquareArrs(-1, n);
}