#include <iostream>
#include <vector>
#include <unordered_map>

using namespace std;

int getRepresent(vector<int> &f, int x)
{
    if (f[x] == x)
    {
        return x;
    }
    int newf = getRepresent(f, f[x]);
    f[x] = newf;
    return newf;
}

void add(vector<int> &f, int x, int y)
{
    int fx = getRepresent(f, x);
    int fy = getRepresent(f, y);
    f[fx] = fy;
}

int minSwapsCouples(vector<int> &people)
{
    int n = people.size();
    int tot = n / 2;
    vector<int> f(tot, 0);
    for (int i = 0; i < tot; i++)
    {
        f[i] = i;
    }

    for (int i = 0; i < n; i += 2)
    {
        int l = people[i] / 2;
        int r = people[i + 1] / 2;
        add(f, l, r);
    }

    unordered_map<int, int> m;
    for (int i = 0; i < tot; i++)
    {
        int fx = getRepresent(f, i);
        m[fx]++;
    }

    int ret = 0;
    for (auto v : m)
    {
        ret += v.second - 1;
    }
    return ret;
}

int main()
{
    int n;
    vector<int> people;
    cin >> n;
    people.resize(n);
    for (int i = 0; i < n; i++)
    {
        cin >> people[i];
    }
    cout << minSwapsCouples(people);
}