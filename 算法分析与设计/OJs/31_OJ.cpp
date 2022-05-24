#include <iostream>

using namespace std;

int lastRemain(int n, int m)
{
    if(n == 1) return 0;
    int x = lastRemain(n - 1, m);
    return (m + x) % n;
}

int main()
{
    int n, m;
    cin >> n;
    cin >> m;
    cout << lastRemain(n, m);
}