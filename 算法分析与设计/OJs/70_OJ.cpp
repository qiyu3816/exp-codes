#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

int n, m;

void maxSatisfiedMonkey()
{
    cin >> n;
    vector<int> monkeys(n);
    for (int i = 0; i < n; i++)
    {
        cin >> monkeys[i];
    }
    cin >> m;
    vector<int> bananas(m);
    for (int i = 0; i < m; i++)
    {
        cin >> bananas[i];
    }
    sort(monkeys.begin(), monkeys.end());
    sort(bananas.begin(), bananas.end());
    int monkeyIndex = n - 1;
    int res = 0;
    for (int i = m - 1; i >= 0; i--)
    {
        for (; monkeyIndex >= 0; monkeyIndex--)
        {
            if (monkeys[monkeyIndex] <= bananas[i])
            {
                monkeyIndex--;
                res++;
                break;
            }
        }
    }
    cout << res << endl;
}

int main()
{
    maxSatisfiedMonkey();
}