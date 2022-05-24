#include <iostream>
#include <string>
#include <vector>
#define MY_MOD 1000'000'007

using namespace std;

int back2ZeroPaths(int steps, int n)
{
    vector<int> directions{-1, 0, 1};
    vector<int> dp(n, 0);
    dp[0] = 1;
    for(int k = 0; k < steps; k++)
    {
        vector<int> tmp(n, 0);
        for(int i = 0; i < n; i++)
        {
            if(dp[i] > 0)
            {
                for(auto direction:directions)
                {
                    int i1 = i + direction;
                    if(i1 < n && i1 >= 0)
                    {
                        tmp[i1] = (tmp[i1] + dp[i]) % MY_MOD;
                    }
                }
            }
        }
        dp = tmp;
    }
    return dp[0];
}

int main()
{
    string line;
    int steps, n;
    getline(std::cin, line);
    steps = stoi(line);
    getline(std::cin, line);
    n = stoi(line);
    cout << back2ZeroPaths(steps, n);
}