#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int k, w, n;
vector<pair<int, int>> projects; // second是利润 first是成本

bool comp(const std::pair<int, int> p1, const std::pair<int, int> p2)
{
    return (p1.first == p2.first ? p1.second < p2.second : p1.first < p2.first);
}

bool comp1(const std::pair<int, int> p1, const std::pair<int, int> p2)
{
    return (p1.second > p2.second);
}

int biggestFinalCapital()
{
    if (k == 0)
        return w;
    sort(projects.begin(), projects.end(), comp);
    // for(int i = 0; i < n; i++)
    // {
    //     cout << projects[i].first << " " << projects[i].second << endl;
    // }
    if (w < projects[0].first)
        return w;

    int res = w, done = 0;
    for(int i = 0; i < n; i++)
    {
        if(projects[i].first > res)
        {
            if(done < i)
            {
                sort(projects.begin(), projects.begin() + i, comp1);
                res += projects[0].second;
                projects[0].second = -1;
                // for(int i = 0; i < n; i++)
                // {
                //     cout << projects[i].first << " " << projects[i].second << endl;
                // }
                done++;
            } else {
                return res;
            }
            i--;
        }
    }
    sort(projects.begin(), projects.end(), comp1);
    if(done < k && done < n)
    {
        for(int i = 0; i < n && projects[i].second != -1 && done + i < k; i++)
            res += projects[i].second;
    }
    return res;
}

int main()
{
    cin >> k >> w;
    cin >> n;
    projects.resize(n);
    for (int i = 0; i < n; i++)
    {
        pair<int, int> p;
        cin >> p.second;
        projects[i] = p;
    }
    cin >> n;
    for (int i = 0; i < n; i++)
    {
        cin >> projects[i].first;
    }
    cout << biggestFinalCapital();
}