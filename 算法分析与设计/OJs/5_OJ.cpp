#include <string>
#include <iostream>

using namespace std;

std::string getLongestRecursiveStr(std::string str)
{
    if(str.empty()) return nullptr;
    if(str.size() == 1) return str;
    if(str.size() == 2 && str[0] == str[1]) return str;
    if(str.size() == 2 && str[0] != str[1]) return str.substr(0, 1);
    int i = 1, res = 1;
    int start = 0, end = 0;
    for(; i < str.size() - 1; i++)
    {
        int tmp = 1;
        int j = i - 1, k = i + 1;
        while(j >= 0 && str[j] == str[i]) {j--, tmp++;}
        while(k < str.size() && str[k] == str[i]) {k++, tmp++;}
        while(j >= 0 && k < str.size())
        {
            if(str[j] == str[k])
            {
                tmp += 2;
            } else {
                break;
            }
            j--;
            k++;
        }
        j++;
        k--;
        if(res < tmp)
        {
            start = j;
            end = k;
            res = tmp;
        }
    }
    return str.substr(start, end - start + 1);
}

int main()
{
    string line;
    while(true)
    {
        getline(std::cin, line);
        cout << getLongestRecursiveStr(line);
        break;
    }
    return 0;
}