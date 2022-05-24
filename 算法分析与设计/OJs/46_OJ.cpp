#include <iostream>
#include <string>
#include <vector>
#include <cstring>

using namespace std;

int result[50001];

int biggestDividedNumsMultiplicity(int n)
{
    if(n == 2) return 1;
    int res = 0;
    for(int i = 1; i < n; i++)
    {
        result[n - i] = (result[n - i] == -1 ? biggestDividedNumsMultiplicity(n - i) : result[n - i]);
        // cout << "result[" << n - i << "]=" << result[n - i] << endl;
        res = max(max(i * result[n - i], i * (n - i)), res);
    }
    return res;
}

int main()
{
    int n;
    string line;
    getline(std::cin, line);
    n = stoi(line);
    memset(result, -1, sizeof(result));
    cout << biggestDividedNumsMultiplicity(n);
}