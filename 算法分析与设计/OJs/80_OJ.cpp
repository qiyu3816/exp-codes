#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>

using namespace std;

int n;
vector<int> nums;

int leastSteps2EqualEachElement()
{
    int sum = 0;
    for(int i = 0; i < n; i++)
    {
        sum += nums[i];
    }
    if(sum % n != 0)
        return -1;
    int target = sum / n;
    int lNeeds = 0, rNeeds = 0;
    vector<int> dp(n);
    for(int i = 0; i < n; i++)
    {
        if(i == 0)
        {
            rNeeds = nums[i] - target;
            // cout << "i=" << i << " l=" << lNeeds << " r=" << rNeeds << endl;
        } else {
            lNeeds += (target - nums[i - 1]);
            rNeeds += (nums[i] - target);
            // cout << "i=" << i << " l=" << lNeeds << " r=" << rNeeds << endl;
            int tmp = lNeeds + rNeeds;
            dp[i] = max((rNeeds >= 0 ? rNeeds : lNeeds), 
                    ((target - nums[i]) >= 0 ? (target - nums[i]) : (nums[i] - target)));
        }
    }
    return *max_element(dp.begin(), dp.end());
}

int main()
{
    cin >> n;
    if(n == 0)
    {
        cout << -1;
        return 0;
    }
    nums.resize(n);
    for(int i = 0; i < n; i++)
    {
        cin >> nums[i];
    }
    cout << leastSteps2EqualEachElement();
}