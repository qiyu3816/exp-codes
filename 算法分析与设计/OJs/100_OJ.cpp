#include <functional>
#include <string>
#include <vector>
#include <iostream>
//#include <algorithm>

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
    int i = 0, sum, kind, num = 0;
    int A[100] = {-1};
    while(true)
    {
        getline(std::cin, line);
        if(i == 0)
        {
            i++;
            ss = splitM(line, ',');
            kind = ss.size();
            for(int j = 0; j < ss.size(); j++)
            {
                A[j] = stoi(ss[j]);
            }
            //sort(A, A + kind, greater<int>());
            for(int j = 0; j < ss.size(); j++)
            {
                int maxi = j;
                for(int k = j; k < ss.size(); k++)
                {
                    if(A[k] > A[maxi])
                        maxi = k;
                }
                int tmp = A[j];
                A[j] = A[maxi];
                A[maxi] = tmp;
            }
        } else {
            sum = stoi(line);
            if(sum == 0)
            {
                cout << 0;
                break;
            }
            for(int k = 0; k < kind && sum != 0; k++)
            {
                if(sum < A[k])
                    continue;
                num += ((sum - (sum % A[k])) / A[k]);
                sum %= A[k];
            }
            if(sum == 0)
                cout << num;
            if(sum != 0)
                cout << -1;
            break;
        }
    }
}
