#include <iostream>
#include <vector>

using namespace std;

int n;
vector<int> nums;

void ifCanReachTheTerminal()
{
    if(nums.empty())
    {
        cout << "false";
        return;
    }
    vector<int> dp(n);
    dp[0] = true;
    for(int i = 0; i < n; i++)
    {
        if(dp[i] == true)
        {
            for(int k = 0; i + k < n && k <= nums[i]; k++)
            {
                dp[i + k] = true;
            }
        }
    }
    cout << (dp[n - 1] == 1 ? "true" : "false");
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
    ifCanReachTheTerminal();
}