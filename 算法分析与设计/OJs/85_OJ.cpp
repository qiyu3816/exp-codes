#include <iostream>
#include <string>
#include <vector>

using namespace std;

string KthWavingStr(int n, int k)
{
    if (n <= 0) return "";
    string ss[3] = {"a", "b", "c"};
    if (n == 1 && k <= 3) return ss[k - 1];
    int kinds = 3;
    for (int i = 1; i < n; i++)
    {
        kinds *= 2;
    }
    if (kinds < k) return "";

    int pos = (k - 1 + kinds / 3) / (kinds / 3); // 在三个初始分区的位置 [1,3]
    k = k - (pos - 1) * (kinds / 3); // 在这个初始分区中的位置 [1,kinds/3]
    int curArea = kinds / 3; // 当前分区大小
    string res = ss[pos - 1];
    int last = pos - 1; // 上一个字符
    for(int i = 1; i < n; i++)
    {
        if (curArea / 2 < k) // 在上半区
        {
            if (last == 2)
                res += ss[1], last = 1;
            else
                res += ss[2], last = 2;
            k -= (curArea / 2);
            curArea /= 2;
        } else if(curArea / 2 >= k) // 在下半区
        {
            if (last == 0)
                res += ss[1], last = 1;
            else
                res += ss[0], last = 0;
            curArea /= 2;
        }
    }
    return res;
}

int main()
{
    int n, k;
    cin >> n;
    cin >> k;
    cout << KthWavingStr(n, k);
}