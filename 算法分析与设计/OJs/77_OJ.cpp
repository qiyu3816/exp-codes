#include <iostream>
#include <queue>
#include <vector>

using namespace std;

int furthestReachedBuilding(vector<int> &heights, int bricks, int ladders)
{
    int n = heights.size();
    priority_queue<int, vector<int>, greater<int>> q;

    int sumH = 0;
    for (int i = 1; i < n; ++i) {
        int deltaH = heights[i] - heights[i - 1];
        if (deltaH > 0) {
            q.push(deltaH);
            if (q.size() > ladders) {
                sumH += q.top();
                q.pop();
            }
            if (sumH > bricks) {
                return i - 1;
            }
        }
    }
    return n - 1;
}

int main()
{
    vector<int> heights;
    int bricks, ladders;
    int n;
    cin >> n;
    heights.resize(n);
    for(int i = 0; i < n; i++)
    {
        cin >> heights[i];
    }
    cin >> bricks;
    cin >> ladders;
    cout << furthestReachedBuilding(heights, bricks, ladders);
}