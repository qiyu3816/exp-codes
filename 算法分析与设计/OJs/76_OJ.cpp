#include <iostream>
#include <vector>
#include <unordered_map>
#define INT_MAX 2147483647
#define INT_MIN (-INT_MAX - 1)

using namespace std;

vector<char> tasks;

int ShortestTimeToFinish(int n)
{
    unordered_map<char, int> taskCnt;
    for (char c:tasks)
    {
        taskCnt[c]++;
    }
    
    // 任务总数
    int m = taskCnt.size();
    vector<int> nextValid, rest;
    for (auto v:taskCnt)
    {
        nextValid.push_back(1);
        rest.push_back(v.second);
    }
    int time = 0;
    for (int i = 0; i < tasks.size(); i++)
    {
        time++;
        int minNextValid = INT_MAX;
        for (int j = 0; j < m; j++)
        {
            if (rest[j])
            {
                minNextValid = min(minNextValid, nextValid[j]);
            }
        }
        time = max(time, minNextValid);
        int best = -1;
        for (int j = 0; j < m; j++)
        {
            if (rest[j] && nextValid[j] <= time)
            {
                if (best == -1 || rest[j] > rest[best])
                {
                    best = j;
                }
            }
        }
        nextValid[best] = time + n + 1;
        rest[best]--;
    }
    return time;
}

int main()
{
    int m;
    cin >> m;
    tasks.resize(m);
    for(int i = 0; i < m; i++)
    {
        cin >> tasks[i];
    }
    int n;
    cin >> n;
    cout << ShortestTimeToFinish(n);
}