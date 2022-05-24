#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include <vector>
#include <algorithm>
#include <sys/time.h>
#define INFINITY 0x3f3f3f3f

using namespace std;

class node
{
public:
    vector<int> reached;          // 已经过的节点
    int depth, curCity, cost, lb; // 已走过的除起点之外城市数量 当前所在城市 当前已花费 当前节点下界

    node(){};
    node(int _depth, int _curCity, int _cost, vector<int> _reached)
    {
        this->depth = _depth;
        this->curCity = _curCity;
        this->cost = _cost;
        this->reached = _reached;
    }

    /**
     * 剩余城市每行最小两个值之和除二向上取整 所有剩余行这样取值之和为当前下界
     */
    void calcLB(vector<vector<int>> &dis)
    {
        int n = dis.size();
        lb = 0;
        for (int i = 0; i < n; i++)
        {
            int sign = 0;
            for (int k = 0; k < depth; k++)
            {
                if (reached[k] == i)
                {
                    sign = 1;
                    break;
                }
            }
            if (!sign)
            {
                int minD1 = INFINITY, minD2 = INFINITY;
                for (int j = 0; j < n; j++)
                {
                    if (dis[i][j] < minD1)
                    {
                        minD2 = minD1;
                        minD1 = dis[i][j];
                    }
                    else if (dis[i][j] < minD2)
                    {
                        minD2 = dis[i][j];
                    }
                }
                lb += (minD1 + minD2 + 1) / 2;
            }
        }
    }

    /**
     * 查询相应城市是否已遍历
     */
    bool Reached(int city)
    {
        for (int i = 0; i <= depth; i++)
        {
            if (reached[i] == city)
                return true;
        }
        return false;
    }

    /**
     * 重载 便于调用sort
     */
    bool operator>(const node &other) const
    {
        return lb > other.lb;
    }

    bool operator<(const node &other) const
    {
        return lb < other.lb;
    }

    bool operator==(const node &other) const
    {
        return lb == other.lb;
    }

private:
};

class BFS
{
public:
    int n;
    vector<vector<int>> dis;
    int bestCost = INFINITY;
    vector<int> bestPath;
    int ub;

    vector<node> lives;

    BFS(){};
    BFS(int num)
    {
        n = num;
        dis = vector<vector<int>>(n, vector<int>(n));
        bestPath = vector<int>(n + 1);
    }

    /**
     * 生成数据
     */
    void randGenerate()
    {
        string filename = to_string(n) + "cities.txt";
        ofstream ofs(filename); // 存储本次随机数据
        time_t t;
        srand((unsigned)time(&t));
        for (int i = 0; i < n; i++)
        {
            dis[i][i] = INFINITY;
            for (int j = i + 1; j < n; j++)
            {
                int d = rand() % 20 + 1; // 全直达
                ofs << i << " " << j << " " << d << "\n";
                dis[i][j] = d, dis[j][i] = d;
            }
        }
        ofs.close();
    }

    /**
     * 解算
     */
    void solve()
    {
        UB();
        for (int j = 1; j < n; j++)
        {
            if (dis[0][j] < INFINITY)
            {
                vector<int> r(n + 1);
                r[0] = 0, r[1] = j;
                node n(1, j, dis[0][j], r);
                n.calcLB(dis);
                lives.push_back(n);
            }
        }
        while (!lives.empty())
            bfs();
    }

private:
    /**
     * 贪心结果作为初始上界
     */
    void UB()
    {
        vector<int> curPath(n + 1);
        int curDepth = 0, curCost = 0;
        curPath[0] = 0;
        ub = dfs(curPath, curDepth, curCost);
        cout << "ub=" << ub << endl;
    }

    /**
     * 贪心深度搜索
     */
    int dfs(vector<int> &curPath, int depth, int curCost)
    {
        int minPos, minD = INFINITY;
        for (int j = 0; j < n; j++)
        {
            if (minD > dis[curPath[depth]][j] && !ifIn(curPath, depth, j))
            {
                minD = dis[curPath[depth]][j];
                minPos = j;
            }
        }
        depth++;
        curPath[depth] = minPos;
        curCost += minD;
        if (depth == n - 1)
            return curCost + dis[minPos][0];
        return dfs(curPath, depth, curCost);
    }

    /**
     * 用于贪心判断是否到达过相应城市
     */
    bool ifIn(vector<int> &curPath, int depth, int city)
    {
        for (int i = 0; i < depth; i++)
        {
            if (curPath[i] == city)
                return true;
        }
        return false;
    }

    /**
     * 广度优先搜索
     */
    void bfs()
    {
        if (lives.empty())
            return;
        for (int i = 0; i < n; i++)
        {
            if (!lives[0].Reached(i))
            {
                int newCost = lives[0].cost + dis[lives[0].curCity][i];
                if (ub < newCost) // 超过上界 剪枝
                    continue;
                if (lives[0].depth == n - 2) // 当前在查询最后一座城市
                {
                    if (bestCost > newCost + dis[i][0] && ub > newCost + dis[i][0])
                    {
                        bestCost = newCost + dis[i][0];
                        bestPath = lives[0].reached;
                        bestPath[n - 1] = i, bestPath[n] = 0;
                    }
                    break;
                }
                vector<int> newReached = lives[0].reached;
                newReached[lives[0].depth + 1] = i;
                node n(lives[0].depth + 1, i, newCost, newReached);
                newReached.clear();
                n.calcLB(dis);
                if (ub < newCost + n.lb)
                    continue; // 下界加上当前花费超过上界 剪枝
                lives.push_back(n);
            }
        }
        lives.erase(lives.begin());
        if (lives.size() == 0)
        {
            return;
        }
        sort(lives.begin(), lives.end());
    }
};

int main(int argc, char **argv)
{
    if (argc != 1 && argc != 3)
    {
        cout << "用法: ./BFS.exe [n] [file.txt]\n";
        cout << "依次为: 可执行文件 城市数(可选) 外部文件输入(可选)\n";
        cout << "文件内容格式为每行按空格分隔三个数，分别为起始点[0,n-1]、终点[0,n-1]、距离，不指定外部文件将内部随机构造\n";
        return 0;
    }

    if (argc == 3) // 使用外部文件输入
    {
        BFS bfs(stoi(argv[1]));
        ifstream ifs(argv[2]);
        int from, end, d;
        bfs.dis[bfs.n - 1][bfs.n - 1] = INFINITY;
        while (ifs >> from >> end >> d)
        {
            bfs.dis[from][from] = INFINITY;
            bfs.dis[from][end] = (d == 0 ? INFINITY : d);
            bfs.dis[end][from] = (d == 0 ? INFINITY : d);
        }
        ifs.close();
        cout << "city num=" << bfs.n << "\n";
        auto begin = clock();
        bfs.solve();
        cout << "time cost=" << (clock() - begin) << "ms\n";
        for (int i = 0; i < bfs.n + 1; i++)
        {
            cout << bfs.bestPath[i] << " ";
        }
        cout << "\n"
             << bfs.bestCost << "\n-------------------------\n";
        return 0;
    }
    else
    { // 内部随机生成输入
        int tests[14] = {10, 11, 12, 13, 14,
                         20, 40, 80, 100, 120,
                         160, 180, 200, 500};
        for (int i = 0; i < 14; i++)
        {
            BFS bfs(tests[i]);
            bfs.randGenerate();
            cout << "city num=" << bfs.n << "\n";

            auto begin = clock();
            bfs.solve();
            cout << "time cost=" << (clock() - begin) << "ms\n";

            for (int i = 0; i < bfs.n + 1; i++)
            {
                cout << bfs.bestPath[i] << " ";
            }
            cout << "\n"
                 << bfs.bestCost << "\n-------------------------\n";
        }
    }

    return 0;
}