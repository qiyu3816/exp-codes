#include <iostream>
#include <string>
#include <vector>

using namespace std;

int n;
vector<int> ele;
vector<int> cost;

void canRideARound()
{
    int dex = n;
    int v;
    int sumE = 0, sumC = 0;
    while(dex--)
    {
        cin >> v;
        sumE += v;
        ele.push_back(v);
    }
    dex = n;
    while(dex--)
    {
        cin >> v;
        sumC += v;
        cost.push_back(v);
    }
    if(sumE < sumC)
    {
        cout << -1;
        return;
    }

    int res = -1;
    for(int i = 0; i < n; i++)
    {
        int can = 1;
        int cur = ele[i] - cost[i];
        for(int j = (i + 1) % n; j != i; j++, j %= n)
        {            
            if(cur < 0)
            {
                can = 0;
                break;
            }
            cur += ele[j];
            cur -= cost[j];
            // cout << "i=" << i << " j=" << j << " cur=" << cur << endl;
        }
        if(can && cur >= 0)
        {
            res = i;
            break;
        }
    }
    cout << res;
}

int main()
{
    cin >> n;
    canRideARound();
}