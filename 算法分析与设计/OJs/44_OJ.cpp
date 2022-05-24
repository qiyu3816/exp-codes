// 有趣的推导
#include <iostream>
#include <iomanip>
#include <string>
#include <vector>

using namespace std;

void correctSeatProbability(int n)
{
    cout << fixed << setprecision(5) << (n == 1 ? 1.0 : 0.5);
}

int main()
{
    string line;
    getline(std::cin, line);
    int n = stoi(line);
    correctSeatProbability(n);
}