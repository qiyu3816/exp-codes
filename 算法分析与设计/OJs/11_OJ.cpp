#include <bits/stdc++.h>

using namespace std;

long long A[101];

long long getFeonachi(long long n)
{
    if(n == 0 || n == 1) return 1;
    if(A[n] == -1)
        A[n] = (getFeonachi(n - 1) + getFeonachi(n - 2)) % 1000000007;
    return A[n] % 1000000007;
}

int main()
{
    memset(A, -1, sizeof(A));
    long long n;
    cin >> n;
    cout << getFeonachi(n);
}