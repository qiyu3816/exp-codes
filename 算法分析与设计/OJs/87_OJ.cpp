#include <iostream>
#include <string>
#include <vector>

using namespace std;

std::vector<std::string> splitM(std::string &str, const char &dilimeter)
{
    std::vector<std::string> res;
    if (str == "")
        return res;

    std::string str1 = str + dilimeter;
    if (str1[0] == dilimeter)
    {
        int i = 1;
        while (str1[i++] == dilimeter && i < str1.length())
            ;
        if (i >= str1.length())
            return res;
        str1 = str1.substr(i - 1, str1.length());
    }
    size_t pos = str1.find(dilimeter);

    std::string tmp;
    while (pos != std::string::npos)
    {
        tmp = str1.substr(0, pos);
        res.push_back(tmp);
        str1 = str1.substr(pos, str1.length());

        if (str1[0] == dilimeter)
        {
            int i = 1;
            while (str1[i++] == dilimeter && i < str1.length())
                ;
            if (i >= str1.length())
                return res;
            str1 = str1.substr(i - 1, str1.length());
        }
        pos = str1.find(dilimeter);
    }

    return res;
}

int directions[4][2] = {{-1, 0}, {1, 0}, {0, 1}, {0, -1}};

// 字符串长度 矩阵行数 列数 当前字符串下标 当前矩阵位置
bool dfs(int size, int m, int n, int index, int line, int column, 
        string &s, vector<string> &ss, vector<vector<int>> &used)
{
    if(size == 0) return false;
    if(s[index] == ss[line][2 * column])
    {
        // cout << index << "=" << line << "," << 2 * column << endl;
        if(index == size - 1)
        {
            return true;
        } else {
            for(int i = 0; i < 4; i++)
            {
                int newLine = line + directions[i][0], newColumn = column + directions[i][1];
                if(newLine >= 0 && newLine < m && newColumn >= 0 && newColumn < n)
                {
                    if(used[newLine][newColumn] == 1) continue;
                    used[newLine][newColumn] = 1;
                    if(dfs(size, m, n, index + 1, newLine, newColumn, s, ss, used))
                        return true;
                    used[newLine][newColumn] = 0;
                }
            }
        }
    }
    return false;
}

void searchStr(int m, int n, string &s, vector<string> &ss)
{
    vector<vector<int>> used(m, vector<int>(n));
    int size = s.size();
    for(int i = 0; i < m; i++)
    {
        for(int j = 0; j < n; j++)
        {
            used[i][j] = 1;
            if(dfs(size, m, n, 0, i, j, s, ss, used))
            {
                cout << "true";
                return;
            }
            used[i][j] = 0;
        }
    }
    cout << "false";
}

int main()
{
    string target, line;
    getline(std::cin, target);
    int m, n;
    getline(std::cin, line);
    m = stoi(line);
    getline(std::cin, line);
    n = stoi(line);

    vector<string> charss(m);
    for (int i = 0; i < m; i++)
    {
        getline(std::cin, charss[i]);
    }

    searchStr(m, n, target, charss);
}