#include <iostream>
#include <string>
#include <vector>

using namespace std;

std::vector<std::string> splitM(std::string &str, const char &dilimeter)
{
    std::vector<std::string> res;
    if(str == "")
        return res;

    std::string str1 = str + dilimeter;
    if(str1[0] == dilimeter)
    {
        int i = 1;
        while(str1[i++] == dilimeter && i < str1.length());
        if(i >= str1.length())
            return res;
        str1 = str1.substr(i - 1, str1.length());
    }
    size_t pos = str1.find(dilimeter);

    std::string tmp;
    while(pos != std::string::npos)
    {
        tmp = str1.substr(0, pos);
        res.push_back(tmp);
        str1 = str1.substr(pos, str1.length());

        if(str1[0] == dilimeter)
        {
            int i = 1;
            while(str1[i++] == dilimeter && i < str1.length());
            if(i >= str1.length())
                return res;
            str1 = str1.substr(i - 1, str1.length());
        }
        pos = str1.find(dilimeter);
    }

    return res;
}

int directions[4][2] = {{-1, 0}, {1, 0}, {0, 1}, {0, -1}};

int dfs(vector<vector<int>> &matrix, int row, int column, vector<vector<int>> &memory)
{
    if (memory[row][column] != 0)
    {
        return memory[row][column];
    }
    memory[row][column]++;
    for (int i = 0; i < 4; i++)
    {
        int newRow = row + directions[i][0], newColumn = column + directions[i][1];
        if (newRow >= 0 && newRow < matrix.size() 
            && newColumn >= 0 && newColumn < matrix[0].size() 
            && matrix[newRow][newColumn] > matrix[row][column])
        {
            memory[row][column] = max(memory[row][column], dfs(matrix, newRow, newColumn, memory) + 1);
        }
    }
    return memory[row][column];
}

int MatrixLongestIncreasingArr(vector<vector<int>> &matrix)
{
    int rows = matrix.size(), columns = matrix[0].size();
    if (rows == 0 || columns == 0)
    {
        return 0;
    }

    auto memory = vector<vector<int>>(rows, vector<int>(columns));
    int ans = 0;
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < columns; j++)
        {
            ans = max(ans, dfs(matrix, i, j, memory));
        }
    }
    return ans;
}

int main()
{
    string line;
    vector<string> ss;
    vector<int> row;
    vector<vector<int>> matrix;
    while(cin >> line)
    {
        ss = splitM(line, ',');
        for(int i = 0; i < ss.size(); i++)
        {
            row.push_back(stoi(ss[i]));
        }
        matrix.push_back(row);
        row.clear();
    }
    cout << MatrixLongestIncreasingArr(matrix);
}