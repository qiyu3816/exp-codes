#include <iostream>
#include <string>
#include <vector>

using namespace std;

int countDiffrentInNumberStr(int n)
{
    int res = 1;
    for(int k = 1; k <= n; k++)
    {
        int tmp = 1;
        for(int i = 1; i <= k; i++)
        {
            tmp *= (10 - (i == 1 ? i : (i - 1)));
        }
        res += tmp;
    }
    return res;
}

int main()
{
    string line;
    getline(std::cin, line);
    int n = stoi(line);
    cout << countDiffrentInNumberStr(n);
}