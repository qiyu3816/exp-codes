#include <iostream>
#include <string>
#include <vector>

using namespace std;

int s;
vector<int> nums;

void canPlantNTrees()
{
    int n;
    cin >> n;
    int count = 0;
    for (int i = 1; i <= s; i++)
    {
        if(nums[i - 1] == 0 && nums[i] == 0 && nums[i + 1] == 0)
        {
            nums[i] = 1;
            count++;
        }
    }
    cout << (count >= n ? "true" : "false");
}

int main()
{
    cin >> s;
    nums.resize(s + 2);
    for (int i = 1; i <= s; i++)
    {
        cin >> nums[i];
    }
    canPlantNTrees();
}