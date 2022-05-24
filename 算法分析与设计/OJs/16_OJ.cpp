#include <iostream>
#include <vector>
#include <string>
#include <cstring>

#define MAX_SIZE 20

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

int size;
vector<int> arr;
int A[MAX_SIZE][MAX_SIZE][MAX_SIZE];

int getGreatestCommonDivisor(int a, int b)
{
    if(a == b) return a;
    int less = a < b ? a : b;
    int tmp = 1, ans = 1;
    for(; tmp <= a; tmp++)
    {
        if(b % tmp == 0 && a % tmp == 0)
            ans = tmp;
    }
    return ans;
}

int getIntegralNum(int size, int ready)
{
    if(size == 2) return (ready + 1) * getGreatestCommonDivisor(arr[0], arr[1]);
    int max = -1, g;
    int tmpi, tmpj;
    for(int i = 0; i < size - 1; i++)
    {
        tmpi = arr[i];
        for(int j = i + 1; j < size; j++)
        {
            tmpj = arr[j];
            arr.erase(arr.begin() + i);
            arr.erase(arr.begin() + j - 1);
            if(max < (g = (ready + 1) * getGreatestCommonDivisor(tmpi, tmpj) + getIntegralNum(size - 2, ready + 1)))
            {
                max = g;
            }
            arr.insert(arr.begin() + i, tmpi);
            arr.insert(arr.begin() + j, tmpj);
        }
    }
    return max;
}

int main()
{
    string line;
    vector<string> ss;
    getline(std::cin, line);
    line = line.substr(1, line.length() - 2);
    ss = splitM(line, ',');
    size = ss.size();
    for(int j = 0; j < ss.size(); j++)
    {
        arr.push_back(stoi(ss[j]));
    }

    memset(A, 0, sizeof(A));
    cout << getIntegralNum(size, 0);
}