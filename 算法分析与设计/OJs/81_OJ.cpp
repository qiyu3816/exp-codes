#include <iostream>
#include <vector>
#include <algorithm>
#define INT_MAX 2147483647
#define INT_MIN (-INT_MAX - 1)

using namespace std;

void dfs(vector<int>& candidates, int target, vector<vector<int>>& res, vector<int>& combine, int idx)
{
    if (idx == candidates.size())
    {
        return;
    }
    if (target == 0)
    {
        res.emplace_back(combine);
        return;
    }

    dfs(candidates, target, res, combine, idx + 1);
    
    if (target - candidates[idx] >= 0)
    {
        combine.emplace_back(candidates[idx]);
        dfs(candidates, target - candidates[idx], res, combine, idx);
        combine.pop_back();
    }
}

int combinationSum(vector<int>& candidates, int target)
{
    vector<vector<int>> res;
    vector<int> combine;
    dfs(candidates, target, res, combine, 0);
    return res.size();
}

int main()
{
    int n;
    int target;
    cin >> target;
    cin >> n;
    vector<int> nums(n);
    for(int i = 0; i < n; i++)
    {
        cin >> nums[i];
    }
    cout << combinationSum(nums, target);
}