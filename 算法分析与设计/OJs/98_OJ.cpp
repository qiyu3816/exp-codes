#include <iostream>
#include <vector>

using namespace std;

vector<int> used;

int LeastCompleteSquares(int n)
{
    if(used[n] != 0) return used[n];
    int res = 0;
    for(int i = 1; i * i <= n; i++)
    {
        if(i == 1)
            res = n + 1;
        if(used[n - i * i] == 0)
        {
            used[n - i * i] = LeastCompleteSquares(n - i * i);
        }
        res = min(res, used[n - i * i] + 1);
    }
    return res;
}

int main()
{
    int n;
    cin >> n;
    used.resize(n + 1);
    cout << LeastCompleteSquares(n);
}