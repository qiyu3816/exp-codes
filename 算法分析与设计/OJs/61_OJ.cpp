#include <iostream>
#include <string>
#include <vector>

using namespace std;

int curL = 0, curA = 0;

// 求a^b
long long powM(long long a, long long b)
{
    long long res = 1;
    for(long long i = 0; i < b; i++)
    {
        res *= a;
    }
    return res;
}

long long able2GetDailyScore(long long n)
{
    if(n == 0 && curL <= 2 && curA < 2) return 1;
    int res = 0;   
    for(int i = 1; i <= 3; i++)
    {
        switch(i)
        {
            case 1:
            {
                int recordL = curL;
                curL = 0;
                curA++;
                if(curA >= 2)
                {
                    curL = recordL;
                    curA--;
                    break;
                } else {
                    res += able2GetDailyScore(n - 1);
                }
                curL = recordL;
                curA--;
                break;
            }
            case 2:
            {
                curL++;
                if(curL > 2)
                {
                    curL--;
                    break;
                } else {
                    res += able2GetDailyScore(n - 1);
                }
                curL--;
                break;
            }
            case 3:
            {
                int recordL = curL;
                curL = 0;
                res += able2GetDailyScore(n - 1);
                curL = recordL;
                break;
            }
            default:
                break;
        }
    }
    return res;
}

int main()
{
    long long n;
    cin >> n;
    cout << able2GetDailyScore(n);
}