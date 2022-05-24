#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <sys/time.h>
#define INFINITY 0x3f3f3f3f

using namespace std;

class GA
{
public:
    int n;
    int dis[501][501];
    int bestCost = INFINITY;
    vector<int> bestPath;

    vector<vector<int>> curPop;
    vector<double> curFitness;
    vector<double> curRoulette; // 从第一个个体到当前个体的适应度比例和
    int initPopulationNum;      // 初始种群规模
    double hybridizationFactor; // 单点交叉概率
    double mutationFactor;      // 变异概率
    int generation;             // 循环代数

    GA(){};
    /**
     * @brief 构造函数
     * 
     * @param num        城市数量
     * @param initPopNum 初始种群规模
     * @param hFactor    交叉概率
     * @param mFactor    变异概率
     * @param gen        循环代数
     */
    GA(int num, int initPopNum, double hFactor, double mFactor, int gen)
    {
        n = num;
        initPopulationNum = initPopNum;
        hybridizationFactor = hFactor;
        mutationFactor = mFactor;
        generation = gen;
        curFitness = vector<double>(initPopulationNum);
        curRoulette = vector<double>(initPopulationNum);
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
        RandomInitialization();

        for (int i = 0; i < generation; i++)
        {
            CalcFitness();

            GambleSelect();

            Hybridization();

            Mutation();
        }

        // 从最后一代得出最终解
        for (int i = 0; i < initPopulationNum; i++)
        {
            int cost = dis[0][curPop[i][0]];
            for (int j = 1; j < n - 1; j++)
            {
                cost += dis[curPop[i][j - 1]][curPop[i][j]];
            }
            cost += dis[curPop[i][n - 2]][0];
            if (cost < bestCost)
            {
                bestPath = curPop[i];
                bestCost = cost;
            }
        }
    }

private:
    /**
     * 随机生成初始种群
     */
    void RandomInitialization()
    {
        curPop = vector<vector<int>>(initPopulationNum, vector<int>(n - 1));
        time_t t;
        srand((unsigned)time(&t));
        for (int i = 0; i < initPopulationNum; i++)
        {
            vector<int> newSingle(n - 1);
            for (int k = 0; k < n - 1; k++)
            {
                newSingle[k] = rand() % (n - 1) + 1;
            }
            repair(newSingle);
            curPop[i] = newSingle;
            for (int r = 0; r < i; r++)
            {
                int equal = 1;
                for (int r1 = 0; r1 < n - 1; r1++)
                {
                    if (curPop[i][r1] != curPop[r][r1])
                    {
                        equal = 0;
                        break;
                    }
                }
                if (equal)
                {
                    i--;
                    break;
                }
            }
        }
    }

    /**
     * 修复有重复基因的个体
     */
    void repair(vector<int> &single)
    {
        vector<int> count(n, 0);
        for (int i = 0; i < n - 1; i++)
        {
            count[single[i]]++;
        }

        int noAppered = 0;
        vector<int> needed;
        for (int i = 1; i < n; i++)
        {
            if (count[i] == 0)
            {
                noAppered++;
                needed.push_back(i);
            }
        }
        if (!noAppered)
            return;
        random_shuffle(needed.begin(), needed.end());

        vector<bool> appeared(n);
        vector<int> blankPos;
        for (int i = 0; i < n - 1; i++)
        {
            if (appeared[single[i]])
            {
                blankPos.push_back(i);
            }
            else
            {
                appeared[single[i]] = true;
            }
        }

        for (int i = 0; i < noAppered; i++)
        {
            single[blankPos[i]] = needed[i];
        }
    }

    /**
     * 计算个体的适应度和轮盘赌选择的比例值
     */
    void CalcFitness()
    {
        double sumFitness = 0.0;
        for (int i = 0; i < initPopulationNum; i++)
        {
            int cost = dis[0][curPop[i][0]];
            for (int j = 1; j < n - 1; j++)
            {
                cost += dis[curPop[i][j - 1]][curPop[i][j]];
            }
            cost += dis[curPop[i][n - 2]][0];
            curFitness[i] = 1.0 / cost;
            sumFitness += curFitness[i];
        }
        for (int i = 0; i < initPopulationNum; i++)
        {
            curFitness[i] = curFitness[i] / sumFitness;
            curRoulette[i] = curRoulette[(i == 0 ? i : i - 1)] + curFitness[i];
        }
    }

    /**
     * 轮盘赌比例选择算法
     */
    void GambleSelect()
    {
        time_t t;
        srand((unsigned)time(&t));
        vector<int> selectedSingle(initPopulationNum);
        vector<int> moreThanOncePos;
        for (int i = 0; i < initPopulationNum; i++)
        {
            double probability = (double)(rand() % 1000 + 1) / 1000.0;
            for (int j = 0; j < initPopulationNum; j++)
            {
                if (curRoulette[j] > probability)
                {
                    selectedSingle[j]++;
                    // cout << j << " ";
                    break;
                }
            }
        }
        for (int i = 0; i < initPopulationNum; i++)
        {
            if (selectedSingle[i] > 1)
                moreThanOncePos.push_back(i);
        }

        for (int i = 0; i < initPopulationNum; i++)
        {
            if (selectedSingle[i] == 0)
            {
                random_shuffle(moreThanOncePos.begin(), moreThanOncePos.end());
                for (int j = 0; j < moreThanOncePos.size(); j++)
                {
                    if (selectedSingle[moreThanOncePos[j]] > 1)
                    {
                        curPop[i] = curPop[moreThanOncePos[j]];
                        selectedSingle[moreThanOncePos[j]]--;
                        break;
                    }
                }
            }
        }
    }

    /**
     * 单点交叉
     */
    void Hybridization()
    {
        time_t t;
        srand((unsigned)time(&t));
        for (int i = 0; i < initPopulationNum / 2; i++)
        {
            double probability = (double)(rand() % 1000 + 1) / 1000.0;
            if (probability < hybridizationFactor) // 随机数决定是否交叉
            {
                double scale = (double)(rand() % 1000 + 1) / 1000.0; // 随机数决定交叉位置
                int index = (int)(scale * (n - 3)) + 1;              // 只能在下标1到n-3之间分割
                // cout << "scale=" << scale << " index=" << index << "\n";
                for (int j = 0; j < index; j++)
                {
                    int tmp = curPop[2 * i][j];
                    curPop[2 * i][j] = curPop[2 * i + 1][j];
                    curPop[2 * i + 1][j] = tmp;
                }
                repair(curPop[2 * i]);
                repair(curPop[2 * i + 1]);
            }
        }
    }

    /**
     * 基本位变异
     */
    void Mutation()
    {
        time_t t;
        srand((unsigned)time(&t));
        for (int i = 0; i < initPopulationNum; i++)
        {
            double probability = (double)(rand() % 1000 + 1) / 1000.0;
            if (probability < mutationFactor) // 随机数决定是否变异
            {

                int index = rand() % (n - 2) + 1; // 在下标0到n-2之间选一个
                int index1 = rand() % (n - 2) + 1;
                while (index1 == index)
                    index1 = rand() % (n - 2) + 1;
                int tmp = curPop[i][index];
                curPop[i][index] = curPop[i][index1];
                curPop[i][index1] = tmp;
            }
        }
    }
};

int main(int argc, char **argv)
{
    if (argc != 1 && argc != 3)
    {
        cout << "用法: ./GA.exe [n] [file.txt]\n";
        cout << "依次为: 可执行文件 城市数(可选) 外部文件输入(可选)\n";
        cout << "文件内容格式为每行按空格分隔三个数，分别为起始点[0,n-1]、终点[0,n-1]、距离，不指定外部文件将内部随机构造\n";
        return 0;
    }

    if (argc == 3) // 使用外部文件输入
    {
        GA ga(stoi(argv[1]), 100, 0.75, 0.001, 300);
        ifstream ifs(argv[2]);
        int from, end, dis;
        ga.dis[ga.n - 1][ga.n - 1] = INFINITY;
        while (ifs >> from >> end >> dis)
        {
            ga.dis[from][from] = INFINITY;
            ga.dis[from][end] = (dis == 0 ? INFINITY : dis);
            ga.dis[end][from] = (dis == 0 ? INFINITY : dis);
        }
        ifs.close();
        cout << "city num=" << ga.n << "\n";
        auto begin = clock();
        ga.solve();
        cout << "time cost=" << (clock() - begin) << "ms\n0 ";
        for (int i = 0; i < ga.n - 1; i++)
        {
            cout << ga.bestPath[i] << " ";
        }
        cout << "0\n"
             << ga.bestCost << "\n-------------------------\n";
        return 0;
    }
    else
    { // 内部随机生成输入
        int tests[14] = {10, 12, 13, 14, 15,
                         20, 40, 80, 100, 120,
                         160, 180, 200, 500};
        for (int i = 0; i < 14; i++)
        {
            GA ga(tests[i], 100, 0.75, 0.005, 300);
            ga.randGenerate();
            cout << "city num=" << ga.n << "\n";

            auto begin = clock();
            ga.solve();
            cout << "time cost=" << (clock() - begin) << "ms\n0 ";

            for (int i = 0; i < ga.n - 1; i++)
            {
                cout << ga.bestPath[i] << " ";
            }
            cout << "0\n"
                 << ga.bestCost << "\n-------------------------\n";
        }
    }

    if(argc != 3)
    {
        // 程序运行完等待5s
        auto begin = clock();
        while((clock() - begin) < 5000);
    }

    return 0;
}