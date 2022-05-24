#include <iostream>
#include <string>

using namespace std;

string target;

string bigNumAdd(string &a, string &b)
{
    string res;
    if (a.size() == 0)
    {
        res = b;
        return res;
    }
    if (b.size() == 0)
    {
        res = a;
        return res;
    }

    res = "";
    int n1 = a.size() - 1, n2 = b.size() - 1;
    int carry = 0;
    while (n1 >= 0 || n2 >= 0)
    {

        int p = (n1 >= 0) ? (a[n1--] - '0') : 0;
        int q = (n2 >= 0) ? (b[n2--] - '0') : 0;

        int t = carry + p + q;
        carry = t / 10;
        t = t % 10;
        res = to_string(t) + res;
    }
    //判断是否还有进位
    while (carry)
    {
        int t = carry / 10;
        carry %= 10;
        res = to_string(carry) + res;
        carry = t;
    }
    return res;
}

bool check(string &first, string &second)
{
    string last = second, last1 = first;
    string cur;
    cur = first + second;
    while (cur.size() < target.size())
    {
        string newO = bigNumAdd(last, last1);
        cur += newO;
        last1 = last;
        last = newO;
    }
    if (cur == target)
        return true;
    return false;
}

void ifFebonachi()
{
    if (target.size() < 3)
    {
        cout << "false";
        return;
    }
    long long size = target.size();
    for (long long i = 1; i <= size - 3; i++)
    {
        if (target[i] == '0')
            continue;
        string first = target.substr(0, i);
        string second;
        for (int j = i + 1; j <= size - 2; j++)
        {
            if (target[j] == '0')
                continue;
            second = target.substr(i, j - i);
            // cout << "first: " << first << "\nsecond: " << second << endl;
            if (check(first, second))
            {
                cout << "true";
                return;
            }
        }
    }
    cout << "false";
    return;
}

int main()
{
    cin >> target;
    ifFebonachi();
}