#include <iostream>
#include <string>
#include <vector>

using namespace std;

string num;

int theHappiestNumber()
{
    int i = 1;
    while(i < num.size() && num[i] - num[i - 1] >= 0) i++;
    if(i < num.size())
    {
        while(i > 0 && num[i - 1] > num[i]) num[i - 1] -= 1, i--;
        for(i++; i < num.size(); i++) num[i] = '9';
    }
    return stoi(num);
}

int main()
{
    getline(std::cin, num);
    cout << theHappiestNumber();
}