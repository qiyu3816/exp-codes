#include <iostream>
#include <string>
#include <vector>
#include <utility>
#include <algorithm>

using namespace std;

int n;

void leastPresentNum()
{
    int dex = 1, v;
    vector<int> nums(n + 2);
    pair<int, int> p[n + 2];
    while(dex <= n)
    {
        cin >> v;
        nums[dex] = v;
        p[dex].first = v, p[dex].second = dex;
        dex++;
    }
    sort(p + 1, p + n + 1);
    vector<int> present(n + 2);
    int res = 0;
    for(int i = 1; i <= n; i++)
    {
        int index = p[i].second;
        int value = p[i].first;
        if(present[index - 1] && value > nums[index - 1])
            present[index] = max(present[index], present[index - 1]);
        if(present[index + 1] && value > nums[index + 1])
            present[index] = max(present[index], present[index + 1]);
        present[index]++;
        res += present[index];
    }
    cout << res;
}

int main()
{
    cin >> n;
    leastPresentNum();
}