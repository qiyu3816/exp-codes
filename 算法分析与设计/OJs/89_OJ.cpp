#include <iostream>
#include <vector>
#include <unordered_set>
#include <stdlib.h>

using namespace std;

int n;
vector<int> points; // points[i] 表示第i行的棋子的列坐标
unordered_set<int> columns;

// 从n行开始
int dfs(int m)
{
    int res = 0;
    for(int i = 0; i < n; i++)
    {
        if(columns.count(i) == 0) // [m - 1][i]
        {
            if(m == n)
            {
                columns.emplace(i);
                points[m - 1] = i;
                res += dfs(m - 1);
                points[m - 1] = -1;
                columns.erase(i);
                continue;
            }
            int sign = 0;
            for(int k = n - 1; k > m - 1; k--)
            {
                if(std::abs(k - m + 1) == std::abs(points[k] - i))
                {
                    sign = 1;
                    break;
                }
            }
            if(sign == 0)
            {
                if(m == 1)
                {
                    // points[m - 1] = i;
                    // for(int p = 0; p < points.size(); p++)
                    // {
                    //     string str = "";
                    //     for(int q = 0; q < points.size(); q++)
                    //     {
                    //         if(q == points[p])
                    //             str += to_string(q);
                    //         else
                    //             str += '-';
                    //     }
                    //     cout << str << endl;
                    // }
                    // cout << ">>>>>>>>>>>>\n";
                    res++;
                }
                else {
                    columns.emplace(i);
                    points[m - 1] = i;
                    res += dfs(m - 1);
                    points[m - 1] = -1;
                    columns.erase(i);
                }
            }
        }
    }
    return res;
}

int nQueen(int n)
{
    points.resize(n);
    if(n == 1) return 1;
    return dfs(n);
}

int main()
{
    cin >> n;
    cout << nQueen(n);
}