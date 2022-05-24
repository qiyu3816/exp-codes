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

vector<int> A, B, C;

void MergeSort()
{
    if(B.empty())
    {
        C = A;
        return;
    }

    int size1 = A.size(), size2 = B.size();
    for(int i = 0, j = 0; i < size1 || j < size2; )
    {
        if(i < size1 && j < size2)
        {
            if(A[i] < B[j])
            {
                C.push_back(A[i]);
                i++;
            } else {
                C.push_back(B[j]);
                j++;
            }
        } else if(i < size1) {
            C.push_back(A[i]);
            i++;
        } else {
            C.push_back(B[j]);
            j++;
        }
    }
}

void getMiddleNum()
{
    int size = C.size();
    if(size % 2 == 0)
    {
        int t = C[size / 2] + C[size / 2 - 1];
        if(t % 2 == 0)
            cout << t / 2;
        else
            cout << t / 2 << ".5";
    }
    else cout << C[size / 2];
}

int main()
{
    string line;
    vector<string> lines;
    while(getline(std::cin, line))
    {
        lines.push_back(line);
    }
    vector<string> ss;
    ss = splitM(lines[0], ',');
    int size = ss.size();
    for(int i = 0; i < size; i++)
    {
        A.push_back(stoi(ss[i]));
    }
    if(lines.size() == 2)
    {
        ss = splitM(lines[1], ',');
        int size = ss.size();
        for(int i = 0; i < size; i++)
        {
            B.push_back(stoi(ss[i]));
        }
    }
    MergeSort();
    getMiddleNum();
}