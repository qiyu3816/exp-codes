#include <iostream>
#include <vector>
#include <string>
#include <cstring>
#define MAX_SIZE 200000

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

vector<int> A;
int C[MAX_SIZE];

inline int lowbit(int v)
{
    return v & -v;
}

void add(int index, int value)
{
    while(index < MAX_SIZE)
    {
        C[index] += value;
        index += lowbit(index);
    }
}

int preSum(int index)
{
    int ret = 0;
    while(index >= 1)
    {
        ret += C[index];
        index -= lowbit(index);
    }
    return ret;
}

int countIdealPairs()
{
    // 树状数组方法
    // int res = 0;
    // if(A.size() < 2) return res;
    // memset(C, 0, sizeof(C));
    // for(int i = A.size() - 1; i >= 0; i--)
    // {
    //     res += preSum(A[i] - 1);
    //     add(2 * A[i], 1);
    // }
    // return res;

    // 暴力方法
    int res = 0;
    if(A.size() < 2) return res;
    for(int i = 0; i < A.size(); i++)
    {
        for(int j = i + 1; j < A.size(); j++)
        {
            if(A[i] > 2 * A[j])
                res++;
        }
    }
    return res;
}

int main()
{
    string line;
    getline(std::cin, line);
    line = line.substr(1, line.length() - 2);
    vector<string> ss = splitM(line, ',');
    for(int i = 0; i < ss.size(); i++)
    {
        A.push_back(stoi(ss[i]));
    }
    cout << countIdealPairs();
}