#include <iostream>
#include <vector>
#include <string>

using namespace std;

string s;

void ifCanBeRecursion()
{
    if(s.empty())
    {
        cout << "false";
        return;
    }
    int size = s.size();
    int sign1 = 1, sign2 = 1;
    string a = s, b = s;
    for(int i = 0; i < size / 2 + 1; i++)
    {
        if(s[i] != s[size - i - 1])
        {
            a.erase(i, 1);
            b.erase(size - i - 1, 1);
        }
    }
    for(int i = 0; i < a.size(); i++)
    {
        if(a[i] != a[a.size() - i - 1])
        {
            sign1 = 0;
            break;
        }
    }
    for(int i = 0; i < b.size(); i++)
    {
        if(b[i] != b[b.size() - i - 1])
        {
            sign2 = 0;
            break;
        }
    }
    cout << ((sign1 == 1 || sign2 == 1) ? "true" : "false");
}

int main()
{
    cin >> s;
    ifCanBeRecursion();
}