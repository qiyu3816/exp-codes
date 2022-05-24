#include <iostream>
#include <vector>
#include <string>
#include <cstring>

using namespace std;

int A[50000];
vector<string> ss;
bool found = false;

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

void ifAble2ReachZero(int start)
{
    int next;
    if(ss[start] == "0")
    {
        found = true;
        cout << "true";
        return;
    }
    if((next = start - stoi(ss[start])) >= 0 && A[next] == 0 && !found)
    {
        A[next] = 1;
        ifAble2ReachZero(next);
    }
    if((next = start + stoi(ss[start])) < ss.size() && A[next] == 0 && !found)
    {
        A[next] = 1;
        ifAble2ReachZero(next);
    }
}

int main()
{
    string line;
    getline(std::cin, line);
    line = line.substr(1, line.length() - 2);
    ss = splitM(line, ',');
    int start;
    cin >> start;
    memset(A, 0, sizeof(A));
    ifAble2ReachZero(start);
    if(!found)
        cout << "false";
}