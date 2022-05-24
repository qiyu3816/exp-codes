#include <iostream>
#include <string>
#include <vector>

using namespace std;

int eatApples(int n)
{
    if(n == 0) return 0;
    if(n == 1) return 1;
    int dp[n + 1];
    dp[0] = 0, dp[1] = 1;
    for(int i = 2; i <= n; i++)
    {
        int eat1 = 1 + dp[i - 1];
        int eatHalf = eat1, eat2_3 = eat1;
        if(i % 2 == 0)
        {
            eatHalf = 1 + dp[i / 2];
        }
        if(i % 3 == 0)
        {
            eat2_3 = 1 + dp[i / 3];
        }
        dp[i] = min(eat1, min(eatHalf, eat2_3));
    }
    return dp[n];
}

int main()
{
    string line;
    getline(std::cin, line);
    int n = stoi(line);
    cout << eatApples(n);
}