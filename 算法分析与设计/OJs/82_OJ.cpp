#include <iostream>
#include <string>
#include <vector>

using namespace std;

int directions[4][2] = {{-1, 0}, {1, 0}, {0, 1}, {0, -1}};

int dfs(int line, int column, int m, int n, vector<vector<int>> &nums)
{
    // cout << "[" << line << "," << column << "]\n";
    // for(int i = 0; i < m; i++)
    // {
    //     for(int j = 0; j < n; j++)
    //     {
    //         cout << nums[i][j] <<  " ";
    //     }
    //     cout << endl;
    // }
    // cout << endl;
    int res = nums[line][column], next = 0;
    for(int k = 0; k < 4; k++)
    {
        int newLine = line + directions[k][0], newColumn = column + directions[k][1];
        if(newLine >= 0 && newLine < m && newColumn >= 0 && newColumn < n && nums[newLine][newColumn] != 0)
        {
            int line_column = nums[line][column];
            nums[line][column] = 0;
            int tmp = dfs(newLine, newColumn, m, n, nums);
            nums[line][column] = line_column;

            next = max(next, tmp);
        }
    }
    return res + next;
}

int maxFloorSum(int m, int n, vector<vector<int>> &nums)
{
    int res = 0;
    for(int i = 0; i < m; i++)
    {
        for(int j = 0; j < n; j++)
        {
            if(nums[i][j] != 0)
            {
                res = max(res, dfs(i, j, m, n, nums));
            }
        }
    }
    return res;
}

int main()
{
    int m, n;
    cin >> m;
    cin >> n;
    vector<vector<int>> nums(m, vector<int>(n));
    for(int i = 0; i < m; i++)
    {
        for(int j = 0; j < n; j++)
        {
            cin >> nums[i][j];
        }
    }
    cout << maxFloorSum(m, n, nums);
}