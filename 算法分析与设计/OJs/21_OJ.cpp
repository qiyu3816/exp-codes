#include <bits/stdc++.h>

using namespace std;

vector<int> process(string s)
{
    vector<int> l, r, res;

    int tmp = 0;
    bool charSign = false;
    char c;
    for(int i = 0; i < s.size(); i++)
    {
        c = s[i];
        if(!isdigit(s[i]))
        {
            charSign = true;
            // cout << s.substr(0, i) << endl;
            l = process(s.substr(0, i));
            // cout << s.substr(i + 1) << endl;
            r = process(s.substr(i + 1));
            for(auto a:l)
            {
                for(auto b:r)
                {
                    switch(c)
                    {
                        case '+':
                            tmp = a + b;
                            break;
                        case '-':
                            tmp = a - b;
                            break;
                        case '*':
                            tmp = a * b;
                            break;
                        default:
                            break;
                    }
                    res.push_back(tmp);
                }
            }
        }
    }
    if(!charSign)
    {
        res.push_back(stoi(s));
        return res;
    }

    return res;
}

int main()
{
    string s;
    cin >> s;
    vector<int> f = process(s);
    int end = f.size();
    for(int i = 0; i < end; i++)
    {
        cout << f[i] << " \n"[i == end - 1];
    }
}