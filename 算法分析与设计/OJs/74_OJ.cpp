#include <iostream>

using namespace std;

void sandwiches(int beefSlices, int cheeseSlices)
{
    if ((beefSlices % 2) != 0)
    {
        cout << "[]";
        return;
    }
    int n = beefSlices / 2 - cheeseSlices, m = 2 * cheeseSlices - beefSlices / 2;
    if (n < 0 || m < 0)
        cout << "[]";
    else
        cout << "[" << n << ", " << m << "]";
}

int main()
{
    int beefSlices, cheeseSlices;
    cin >> beefSlices;
    cin >> cheeseSlices;
    sandwiches(beefSlices, cheeseSlices);
}