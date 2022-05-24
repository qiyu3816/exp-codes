#include <iostream>
#include <vector>
#include <string>

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

int main()
{
    string line;
    vector<string> ss;
    int i = 0;
    int a, b;
    vector<int> A, B;
    while(true)
    {
        getline(std::cin, line);
        if(!line.empty())
        {
            if(i == 0)
            {
                i++;
                a = stoi(line);
                continue;
            }
            if(i == 1)
            {
                i++;
                if(a != 0)
                {
                    ss = splitM(line, ' ');
                    for(int j = 0; j < ss.size(); j++)
                    {
                        A.push_back(stoi(ss[j]));
                    }
                } else {
                    b = stoi(line);
                }
                continue;
            }
            if(i == 2)
            {
                i++;
                if(a != 0)
                {
                    b = stoi(line);
                    if(b == 0)
                    {
                        for(int j = 0; j < A.size(); j++)
                        {
                            cout << A[j] << " ";
                        }
                        break;
                    }
                } else if(b != 0) {
                    ss = splitM(line, ' ');
                    for(int j = 0; j < ss.size(); j++)
                    {
                        B.push_back(stoi(ss[j]));
                    }
                    for(int j = 0; j < B.size(); j++)
                    {
                        //if(j == B.size() - 1)
                        //{
                        //    cout << B[j];
                        //    break;
                        //}
                        cout << B[j] << " ";
                    }
                    break;
                } else if(b == 0) {
                    break;
                }
                continue;
            }
            if(i == 3)
            {
                ss = splitM(line, ' ');
                int k = 0;
                for(int j = 0; j < ss.size(); j++)
                {
                    B.push_back(stoi(ss[j]));
                    if(k == A.size())
                    {
                        A.push_back(B[j]);
                        continue;
                    }
                    for(; k < A.size() && A[k] <= B[j]; k++) {}
                    A.insert(A.begin() + k, B[j]);
                    k++;
                }
                for(int i = 0; i < A.size(); i++)
                {
                    cout << A[i] << " ";
                }
                break;
            }
        }
    }
}
