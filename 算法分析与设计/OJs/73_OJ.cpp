#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

int n;
vector<int> nums;

int countTriangleMethods()
{
    if (nums.size() < 3)
        return 0;
    n = nums.size();
    sort(nums.begin(), nums.end());
    int res = 0;
    for (int i = 0; i < n; ++i)
    {
        int k = i;
        for (int j = i + 1; j < n; ++j)
        {
            while (k + 1 < n && nums[k + 1] < nums[i] + nums[j])
            {
                k++;
            }
            res += max(k - j, 0);
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
    cout << countTriangleMethods();
}