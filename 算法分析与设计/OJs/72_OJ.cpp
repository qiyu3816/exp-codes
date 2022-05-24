#include <iostream>
#include <string>

using namespace std;

int TotalBottles(int n, int ex)
{
    int result = n;
    int cur = n;
    while(cur >= ex)
    {
        result += (cur / ex);
        int tmp = (cur / ex);
        cur %= ex;
        cur += tmp;
    }
    return result;
}

int main()
{
    string line;
    getline(std::cin, line);
    int n = stoi(line);
    getline(std::cin, line);
    int ex = stoi(line);
    cout << TotalBottles(n, ex);
}