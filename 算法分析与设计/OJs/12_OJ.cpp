#include <iostream>
#include <string>
#include <vector>

using namespace std;

vector<string> res;

void subPrint(string lastStr, int last, int k, int rest)
{
    if(last - k >= 0)
    {
        string tmp = lastStr;
        tmp += to_string(last - k);
        if(rest == 1)
        {
            res.push_back(tmp);
        } else {
            subPrint(tmp, last - k, k, rest - 1);
        }
    }
    if(last + k <= 9)
    {
        string tmp = lastStr;
        tmp += to_string(last + k);
        if(rest == 1)
        {
            res.push_back(tmp);
        } else {
            subPrint(tmp, last + k, k, rest - 1);
        }
    }
}

void printQuWeiShu(int n, int k)
{
    if(n < 2 || k < 0 || k > 9) return;
    for(int i = 1; i <= 9; i++)
    {
        if(k == 0)
        {
            string tmp;
            for(int j = 0; j < n; j++)
            {
                tmp += to_string(i);
            }
            res.push_back(tmp);
            continue;
        }
        subPrint(to_string(i), i, k, n - 1);
    }
    cout << "[";
    for(int i = 0; i < res.size(); i++)
    {
        if(i == res.size() - 1)
        {
            cout << res[i];
            break;
        }
        cout << res[i] << ",";
    }
    cout << "]";
}

int main()
{
    int n, k;
    cin >> n;
    cin >> k;
    printQuWeiShu(n, k);
}