#include <iostream>
#include <vector>
#include <string>
#include <cstring>

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

void findNthMin(vector<string> &ss, int n)
{
    if(ss.empty() || n <= 0 || ss.size() < n)
    {
        cout << "[]";
        return;
    }
    vector<int> minn;
    for(int i = 0; i < ss.size(); i++)
    {
        int tmp = stoi(ss[i]);
        if(minn.size() == n)
        {
            for(int j = 0; j < n; j++)
            {
                if(minn[j] > tmp)
                {
                    for(int k = n - 1; k > j; k--)
                    {
                        minn[k] = minn[k - 1];
                    }
                    minn[j] = tmp;
                    break;
                }
            }
        } else {
            bool found = false;
            for(int j = 0; j < minn.size(); j++)
            {
                if(minn[j] > tmp)
                {
                    found = true;
                    minn.insert(minn.begin() + j, tmp);
                    break;
                }
            }
            if(!found)
                minn.push_back(tmp);
        }
    }
    
    cout << "[";
    for(int i = 0; i < minn.size(); i++)
    {
        if(i == minn.size() - 1)
        {
            cout << minn[i];
            break;
        }
        cout << minn[i] << ", ";
    }
    cout << "]";
}

int main()
{
    string line;
    getline(std::cin, line);
    int n;
    cin >> n;
    line = line.substr(1, line.length() - 2);
    vector<string> ss = splitM(line, ',');
    findNthMin(ss, n);
}