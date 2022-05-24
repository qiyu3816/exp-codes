#include <iostream>
#include <vector>
#include <unordered_set>

using namespace std;

unordered_set<int> used;
vector<int> matching;
vector<vector<int>> match;

void findMatch(int cur, int rest, int required)
{   
    for(int i = 1; i <= required; i++)
    {
        // cout << "cur " << cur << " i " << i << endl;
        if(i % cur == 0 || cur % i == 0)
        {
            // cout << "i " << i << " fits cur " << cur << " rest " << rest << endl;
            if(used.find(i) == used.end())
            {
                // cout << "i not used!!!\n";
                used.emplace(i);
                matching.push_back(i);
                if(rest - 1 == 0)
                {
                    used.erase(i);
                    match.push_back(matching);
                    // cout << "found ";
                    // for(auto a:matching)
                    //     cout << a << " ";
                    // cout << endl;
                    matching.erase(matching.begin() + cur - 1);
                    return;
                }
                findMatch(cur + 1, rest - 1, required);
                used.erase(i);
                matching.erase(matching.begin() + cur - 1);
            }
        }
    }
}

int getPerfectArrayNum(int n)
{
    if(n < 2) return 1;
    findMatch(1, n, n);
    return match.size();
}

int main()
{
    int n;
    cin >> n;
    cout << getPerfectArrayNum(n);
}