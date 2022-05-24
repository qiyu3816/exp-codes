#include <iostream>
#include <string>
#include <algorithm>

using namespace std;

string line;
int k;

void reverseM()
{
    int size = line.size();
    string tmp;
    for(int i = 0; i < size; i += 2 * k)
    {
        
        if(i + 2 * k >= size)
        {
            tmp = line.substr(i, k);
            reverse(tmp.begin(), tmp.end());
            cout << tmp << line.substr(i + k, size - i - k);
        } else if(i + 2 * k >= size) {
            tmp = line.substr(i, size - i);
            reverse(tmp.begin(), tmp.end());
            cout << tmp;
        } else {
            tmp = line.substr(i, k);
            reverse(tmp.begin(), tmp.end());
            cout << tmp << line.substr(i + k, k);
        }
        
    }
}

int main()
{
    getline(std::cin, line);
    cin >> k;
    reverseM();
}