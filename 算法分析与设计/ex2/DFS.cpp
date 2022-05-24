#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include <vector>
#include <sys/time.h>
#define INFINITY 0x3f3f3f3f

using namespace std;

class DFS
{
public:
    int n;
    int dis[501][501];
    int bestCost = INFINITY;
    vector<int> bestPath;
    vector<int> curPath;

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
        bestPath = vector<int>(n + 1);
        curPath = vector<int>(n + 1);
        curPath[0] = 0;

        for (int j = 1; j < n; j++)
        {
            if (dis[0][j] < INFINITY)
            {
                curPath[1] = j;
                dfs(j, 2, dis[0][j]);
            }
        }
    }

private:
    /**
     * 剩余城市每行最小值的和为下界
     */
    int LB(int city, int curReached)
    {
        int lb = 0;
        for (int i = 0; i < n; i++)
        {
            if (ifReached(i, curReached) && i != city)
                continue;
            int minD = INFINITY;
            for (int j = 0; j < n; j++)
            {
                minD = min(dis[i][j], minD);
            }
            lb += minD;
        }
        return lb;
    }

    /**
     * 深度优先搜索
     */
    void dfs(int curCity, int curReached, int curCost)
    {
        for (int j = 1; j < n; j++)
        {
            if (bestCost < curCost + LB(curCity, curReached))
                continue; // 最优性剪枝
            if (bestCost < curCost + dis[curCity][j])
                continue; // 已经不小于当前最优解 剪枝
            if (dis[curCity][j] < INFINITY && !ifReached(j, curReached))
            {
                curPath[curReached] = j;
                if (curReached == n - 1)
                {
                    if (dis[j][0] == INFINITY)
                        continue; // 最后一座城市无法回到起点 剪枝
                    if (bestCost > curCost + dis[curCity][j] + dis[j][0])
                    {
                        curPath[curReached + 1] = 0;
                        bestCost = curCost + dis[curCity][j] + dis[j][0];
                        bestPath = curPath;
                    }
                    return;
                }
                dfs(j, curReached + 1, dis[curCity][j] + curCost);
            }
        }
    }

    /**
     * 验证当前城市是否抵达过
     */
    bool ifReached(int city, int curReached)
    {
        for (int i = 0; i < curReached; i++)
        {
            if (city == curPath[i])
                return true;
        }
        return false;
    }
};

int main(int argc, char **argv)
{
    if (argc != 1 && argc != 3)
    {
        cout << "用法: ./DFS.exe [n] [file.txt]\n";
        cout << "依次为: 可执行文件 城市数(可选) 外部文件输入(可选)\n";
        cout << "文件内容格式为每行按空格分隔三个数，分别为起始点[0,n-1]、终点[0,n-1]、距离，不指定外部文件将内部随机构造\n";
        return 0;
    }

    if (argc == 3) // 使用外部文件输入
    {
        DFS dfs;
        dfs.n = stoi(argv[1]);
        ifstream ifs(argv[2]);
        int from, end, dis;
        dfs.dis[dfs.n - 1][dfs.n - 1] = INFINITY;
        while (ifs >> from >> end >> dis)
        {
            dfs.dis[from][from] = INFINITY;
            dfs.dis[from][end] = (dis == 0 ? INFINITY : dis);
            dfs.dis[end][from] = (dis == 0 ? INFINITY : dis);
        }
        ifs.close();
        cout << "city num=" << dfs.n << "\n";
        auto begin = clock();
        dfs.solve();
        cout << "time cost=" << (clock() - begin) << "ms\n";
        for (int i = 0; i < dfs.n + 1; i++)
        {
            cout << dfs.bestPath[i] << " ";
        }
        cout << "\n"
             << dfs.bestCost << "\n-------------------------\n";
        return 0;
    }
    else
    { // 内部随机生成输入
        int tests[14] = {10, 12, 13, 14, 15,
                         20, 40, 80, 100, 120,
                         160, 180, 200, 500};
        for (int i = 0; i < 14; i++)
        {
            DFS dfs;
            dfs.n = tests[i];
            dfs.randGenerate();
            cout << "city num=" << dfs.n << "\n";

            auto begin = clock();
            dfs.solve();
            cout << "time cost=" << (clock() - begin) << "ms\n";

            for (int i = 0; i < dfs.n + 1; i++)
            {
                cout << dfs.bestPath[i] << " ";
            }
            cout << "\n"
                 << dfs.bestCost << "\n-------------------------\n";
        }
    }

    return 0;
}