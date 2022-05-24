#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

bool nextArrange(string &s)
{
    int i = s.size() - 2;
    while (i >= 0 && s[i] >= s[i + 1])
    {
        i--;
    }
    if (i < 0)
    {
        return false;
    }
    int j = s.size() - 1;
    while (j >= 0 && s[i] >= s[j])
    {
        j--;
    }
    swap(s[i], s[j]);
    reverse(s.begin() + i + 1, s.end());
    return true;
}

void allArrange(string s)
{
    vector<string> res;
    sort(s.begin(), s.end());
    do
    {
        res.push_back(s);
    } while (nextArrange(s));
    for(int i = 0; i < res.size(); i++)
    {
        if(i == res.size() - 1)
        {
            cout << res[i];
            break;
        }
        cout << res[i] << std::endl;
    }
}

int main()
{
    string s;
    cin >> s;
    allArrange(s);
}