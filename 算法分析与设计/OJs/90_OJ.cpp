#include <iostream>
#include <string>
#include <vector>
#include <cstring>
#include <bitset>

using namespace std;

vector<int> cnt;
vector<string> ss;
int m = 0;

int exp2(int x)
{
    int res = 1;
    while(x--)
    {
        res *= 2;
    }
    return res;
}

int longestCombinedNoneRepeatStr()
{
    if(m == 0) return 0;
    vector<int> dp1[m + 1][27];
    int res = 0;
    for(int i = 1; i <= m; i++)
    {
        for(int k = 0; k < i; k++)
        {
            int l = ss[k].length();
            res = max(res, l);
            dp1[i][l].push_back(cnt[k]);
        }
    }

    // for(int p = 0; p <= m; p++)
    // {
    //     for(int q = 0; q <= 26; q++)
    //     {
    //         if(dp1[p][q].size() == 0)
    //             continue;
    //         cout << "[" << p << "," << q << "]=";
    //         for(int a:dp1[p][q])
    //         {
    //             cout << a << " ";
    //         }
    //         cout << endl;
    //     }
    // }

    for(int i = 2; i <= m; i++)
    {
        for(int j = 1; j <= 26; j++)
        {
            // cout << "\n<------------->\n";
            for(int a:dp1[i - 1][j])
            {
                dp1[i][j].push_back(a);
            }
            // cout << "dp[" << i << "][" << j << "]" << (dp1[i][j].size() > 0 ? "rawhav\n" : "rawnot\n");
            
            int l = ss[i - 1].length();
            if(j - l >= 0)
            {
                for(int a:dp1[i - 1][j - l])
                {
                    if((a & cnt[i - 1]) == 0)
                    {
                        dp1[i][j].push_back(cnt[i - 1] | a);
                        // cout << "[" << i - 1 << "," << j - l << "]&cnt\n"
                        // << bitset<26>(a) << "\n"
                        // << bitset<26>(cnt[i - 1]) << "\n"
                        // << bitset<26>(cnt[i - 1] | a) << "correct\n";
                    }
                    // else{
                    //     cout << "[" << i - 1 << "," << j - l << "]&cnt\n"
                    //     << bitset<26>(a) << "\n"
                    //     << bitset<26>(cnt[i - 1]) << "wrong\n";
                    // }
                }
            }

            // for(int p = 0; p <= m; p++)
            // {
            //     for(int q = 0; q <= 26; q++)
            //     {
            //         if(dp1[p][q].size() == 0)
            //             continue;
            //         cout << "[" << p << "," << q << "]=";
            //         for(int a:dp1[p][q])
            //         {
            //             cout << bitset<26>(a) << " ";
            //         }
            //         cout << endl;
            //     }
            // }
            // cout << endl;
            
            if(dp1[i][j].size() > 0)
                res = max(res, j);
            if(res == 26) return 26;
        }
    }
    return res;
}

int main()
{
    string line;
    int n;
    cin >> n;
    while(n--)
    {
        int chars = 0;
        cin >> line;
        int sign = 1;
        for(auto c:line)
        {
            if((chars & exp2(c - 'a')) != 0)
            {
                sign = 0;
                break;
            }
            chars += exp2(c - 'a');
        }
        if(sign)
        {
            // cout << "line=" << line << endl;
            // cout << bitset<26>(chars) << endl;
            ss.push_back(line);
            cnt.push_back(chars);
            m++;
        }
    }

    cout << longestCombinedNoneRepeatStr();
}