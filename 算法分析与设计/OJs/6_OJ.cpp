#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

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

void outputTrilateralSumZero(int input[], int length)
{
    if(length < 3) return;
    int i = 0;
    int front, back;
    for(; i < length - 2; i++)
    {
        if(i != 0)
        {
            while(input[i] == input[i - 1] && i < length) {i++;}
        }
        for(back = i + 1, front = back + 1; back < length - 1; back++)
        {
            if(back != i + 1)
            {
                while(input[back] == input[back - 1] && back < length - 1) {back++;}
                front = back + 1;
            }
            for(; front < length; front++)
            {
                if(front != back + 1)
                {
                    while(input[front] == input[front - 1] && front < length) {front++;}
                }
                if(input[i] + input[back] + input[front] == 0)
                {
                    cout << input[i] << " " << input[back] << " " << input[front] << " \n";
                }
            }
        }
    }
}

int main()
{
    string line;
    vector<string> ss;
    int i = 0;
    int a;
    while(true)
    {
        getline(std::cin, line);
        if(i == 0)
        {
            i++;
            a = stoi(line);
            continue;
        }
        ss = splitM(line, ' ');
        int A[a];
        for(int j = 0; j < ss.size(); j++)
        {
            A[j] = stoi(ss[j]);
        }
        sort(A, A + a, less<int>());
        outputTrilateralSumZero(A, a);
        break;
    }
}