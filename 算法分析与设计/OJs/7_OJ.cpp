#include <iostream>
#include <vector>
#include <string>

using namespace std;

int main()
{
    string line;
    vector<string> ss;
    int t = 0;
    int a, win;
    while(true)
    {
        if(t == 0)
        {
            cin >> a;
            t++;
        }
        int A[a];
        
        for(int i = 0; i < a; i++)
        {
            cin >> A[i];
        }
        vector<int> res;
        cin >> win;
        if(a < win || a == 0 || win == 0)
        {
            return 0;
        }
        int k = 0, max = A[0], pos = 0;
        for(int i = 0; i < win; i++)
        {
            if(A[i] >= max) max = A[i], pos = i;
        }
        res.push_back(max);
        for(int i = win; i < a; i++)
        {
            if (pos == i - win) {
                max = A[i - win + 1];
                for(int j = i - win + 1; j <= i; j++)
                {
                    if(max <= A[j]) max = A[j], pos = j;
                }
                res.push_back(max);
            } else if (max <= A[i]) {
                max = A[i], pos = i;
                res.push_back(max);
            } else {
                res.push_back(max);
            }
        }
        for(int k = 0; k < res.size(); k++)
        {
            if(k == res.size() - 1)
            {
                cout << res[k];
                break;
            }
            cout << res[k] << " ";
        }
        break;
    }
}