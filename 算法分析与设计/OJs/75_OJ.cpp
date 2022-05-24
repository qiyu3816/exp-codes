#include <iostream>
#include <vector>
#include <algorithm>

const int INF = 0x3f3f3f3f;

using namespace std;

int BestPeaches(int n, vector<int> &peaches, vector<int> &days)
{
    int res = 0;
    for (int i = 0; ; i++)
    {
        int minDaysIndex = -1, minDays = INF;
        for (int j = 0; j <= i && j < n; j++)
        {
            if(peaches[j] > 0 && days[j] < minDays && days[j] + j > i)
            {
                minDaysIndex = j;
                minDays = days[j];
            }
        }
        // cout << "minDaysIndex: " << minDaysIndex << endl;
        if(minDaysIndex != -1)
        {
            peaches[minDaysIndex]--;
            res++;
        }
        if(minDaysIndex == -1 && i >= n) break;
    }
    return res;
}

int main()
{
    int n;
    cin >> n;
    vector<int> peaches(n);
    for (int i = 0; i < n; i++)
    {
        cin >> peaches[i];
    }
    cin >> n;
    vector<int> days(n);
    for (int i = 0; i < n; i++)
    {
        cin >> days[i];
    }
    cout << BestPeaches(n, peaches, days);
}