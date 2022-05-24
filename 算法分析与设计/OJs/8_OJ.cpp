#include <iostream>
#include <vector>
#include <string>

using namespace std;
static vector<char> source;
static vector<char> tmp;
vector<vector<char>> generateChar(int size, int pos)
{
    static vector<vector<char>> result;
    pos++;
    for(int i = 0; i < source.size(); i++)
    {
        tmp[pos] = source[i];
        if(pos < size - 1)
        {
            generateChar(size, pos);
        } else {
            result.push_back(tmp);
        }
    }
    return result;
}

void printEquals(int A[], int length)
{
    vector<vector<char>> charss = generateChar(length - 2, -1);
    for(auto chars:charss)
    {
        vector<int> B;
        for(int i = 0; i < length; i++)
        {
            B.push_back(-1);
        }
        vector<char> charsT = chars;
        for(int j = 0; j < length; j++)
        {
            B[j] = A[j];
        }
        for(int i = 0; i < charsT.size(); i++)
        {
            if(charsT[i] == '*')
            {
                charsT.erase(charsT.begin() + i);
                B[i] = B[i] * B[i + 1];
                B.erase(B.begin() + i + 1);
                i--;
            } else if(charsT[i] == '/') {
                charsT.erase(charsT.begin() + i);
                B[i] = B[i] / B[i + 1];
                B.erase(B.begin() + i + 1);
                i--;
            }
        }
        for(int i = 0; i < charsT.size(); i++)
        {
            if(charsT[i] == '+')
            {
                charsT.erase(charsT.begin() + i);
                B[i] = B[i] + B[i + 1];
                B.erase(B.begin() + i + 1);
                i--;
            } else if(charsT[i] == '-') {
                charsT.erase(charsT.begin() + i);
                B[i] = B[i] - B[i + 1];
                B.erase(B.begin() + i + 1);
                i--;
            }
        }
        if(B[0] == B[1])
        {
            string res;
            for(int k = 0; k < length - 2; k++)
            {
                res += to_string(A[k]) + chars[k];
            }
            res += to_string(A[length - 2]) + "=" + to_string(A[length - 1]);
            cout << res << endl;
        }
    }
}

int main()
{
    int a = 6;
    int A[a];
    source = {'+', '-', '*', '/'};
    for(int i = 0; i < a; i++)
    {
        cin >> A[i];
    }
    for(int i = 0; i < a - 2; i++)
    {
        tmp.push_back(' ');
    }
    printEquals(A, 6);
}