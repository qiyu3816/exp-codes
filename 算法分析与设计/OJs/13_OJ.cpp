#include <iostream>
#include <string>
#include <cmath>

using namespace std;

string getReverse(string s)
{
    for(int i = 0; i < s.length(); i++)
    {
        s[i] = s[i] == '0' ? '1' :'0';
    }
    return s;
}

string getReplaceGame(int n)
{
    string res;
    if(n == 0) return res;
    if(n == 1) return "0";
    string last = getReplaceGame(n - 1);
    res = last + getReverse(last);
    return res;
}

char getTargetFromReplaceGame(int n, int t)
{
    if(n == 1) return '0';
    if(t <= pow(2, n - 2))
    {
        return getTargetFromReplaceGame(n - 1, t);
    } else {
        return getTargetFromReplaceGame(n - 1, t - pow(2, n - 2)) == '0' ? '1' : '0';
    }
}

int main()
{
    int n, t;
    cin >> n;
    cin >> t;
    cout << getTargetFromReplaceGame(n, t);
}