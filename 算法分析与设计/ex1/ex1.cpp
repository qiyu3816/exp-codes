#include <iostream>
#include <vector>
#include <iomanip>

using namespace std;

int n;

void ProbabilityToPromote()
{
    int m = n * 0.7 + ((n % 10) == 0 ? 0 : 1);
    vector<double> p(n + 1), dp(n + 1);
    dp[0] = 1;
    for (int i = 1; i <= n; i++)
    {
    	cin >> p[i];
    	p[i] /= 100.0;
    }
    for (int i = 1; i <= n; i++)
    {
        for (int j = n; j > 0; j--)
        {
            dp[j] = dp[j - 1] * p[i] + dp[j] * (1.0 - p[i]);
        }
        dp[0] *= (1.0 - p[i]);
    }
    double res = 0;
    // 至少赢m局的情况概率相加
    for (int i = m; i <= n; i++) res += dp[i];
    cout << setprecision(5) << res;
}
int main()
{
    cin >> n;
	ProbabilityToPromote();
    return 0;
}
