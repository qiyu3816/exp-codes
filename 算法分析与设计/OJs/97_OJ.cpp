#include <iostream>

using namespace std;

// 前6个灯唯一决定所有灯 x+6=x
// 前3个灯可以唯一表示最终状态 每3个灯为一个最小的共同受影响单元
int NLightsMOperations(int n, int m)
{
    n = min(n, 3);
    int m1[3] = {2, 3, 4}, m2[3] = {2, 3, 7};
    if(m == 0) return 0;
    if(m == 1) return m1[n - 1];
    if(m == 2) return m2[n - 1];
    int m4[3] = {2, 4, 8};
    return m4[n - 1];
}

int main()
{
    int n, m;
    cin >> n;
    cin >> m;
    cout << NLightsMOperations(n, m);
}