#include <iostream>
#include <vector>
#include <string>

using namespace std;

void dfs(int n, string path, vector<string> &res, int right, int left)
{
    if (right > n || left > right)
        return;

    if (path.length() == 2 * n)
    {
        res.push_back(path);
        return;
    }

    dfs(n, path + "(", res, right + 1, left);
    dfs(n, path + ")", res, right, left + 1);
}

int legalMatchCnt(int n)
{
    vector<string> res;
    if (n <= 0)
        return 0;
    dfs(n, "", res, 0, 0);
    return res.size();
}

int main()
{
    int n;
    cin >> n;
    cout << legalMatchCnt(n);
}