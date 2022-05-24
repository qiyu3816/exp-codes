#include <iostream>
#include <vector>

using namespace std;

int n;
vector<int> nums;

int mostInterest()
{
    if(n == 0) return 0;
    if(n == 1) return nums[0];
    vector<vector<int>> dp(n, vector<int>(n));
    int res = 0;
    for(int i = 0; i < n; i++) dp[i][i] = nums[i];
    for(int i = 0; i < n; i++)
    {
        for(int j = (i + 1) % n; j != i; j++, j %= n)
        {
            if((j > i && (j - i) >= 2 && (n - j + i) >= 2) || (i > j && (i - j) >= 2 && (n - i + j) >= 2))
            {
                dp[i][j] = max(dp[i][(j + n - 1) % n], dp[i][(j + n - 2) % n] + nums[j]);
                // cout << "1dp[" << i << "][" << j << "]=" << dp[i][j] << endl;
                res = max(res, dp[i][j]);
            } else {
                dp[i][j] = dp[i][(j + n - 1) % n];
                // cout << "2dp[" << i << "][" << j << "]=" << dp[i][j] << endl;
                res = max(res, dp[i][j]);
            }
        }
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
    cout << mostInterest();
}