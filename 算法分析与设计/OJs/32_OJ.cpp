#include <iostream>
#include <string>
#include <vector>
#include <cmath>

#define MY_MOD 1337

using namespace std;

std::vector<std::string> splitM(std::string &str, const char &dilimeter)
{
    std::vector<std::string> res;
    if (str == "")
        return res;

    std::string str1 = str + dilimeter;
    if (str1[0] == dilimeter)
    {
        int i = 1;
        while (str1[i++] == dilimeter && i < str1.length())
            ;
        if (i >= str1.length())
            return res;
        str1 = str1.substr(i - 1, str1.length());
    }
    size_t pos = str1.find(dilimeter);

    std::string tmp;
    while (pos != std::string::npos)
    {
        tmp = str1.substr(0, pos);
        res.push_back(tmp);
        str1 = str1.substr(pos, str1.length());

        if (str1[0] == dilimeter)
        {
            int i = 1;
            while (str1[i++] == dilimeter && i < str1.length())
                ;
            if (i >= str1.length())
                return res;
            str1 = str1.substr(i - 1, str1.length());
        }
        pos = str1.find(dilimeter);
    }

    return res;
}

long long a;
vector<long long> B;

long long getEuler(long long n)
{
    int m = int(sqrt(n + 0.5));
    int ans = n;
    for (int i = 2; i <= m; i++)
        if (n % i == 0)
        {
            ans = ans / i * (i - 1);
            while (n % i == 0)
                n /= i;
        }
    if (n > 1)
        ans = ans / n * (n - 1);
    return ans;
}

long long getBigExponent()
{
    if(B.size() == 0) return 0;
    long long m = a % MY_MOD;
    long long phi_my_mod = getEuler(MY_MOD);
    long long size = B.size();
    long long q = 0;
    for(int i = 0; i < size; i++)
    {
        q = ((B[i] + 10 * q) % phi_my_mod);
    }
    // cout << "m " << m << " phi_my_mod " << phi_my_mod << " q " << q << endl;
    long long res = 1;
    for(int i = 0; i < phi_my_mod + q; i++)
    {
        res *= m;
        res %= MY_MOD;
    }
    return res;
}

int main()
{
    string line;
    getline(std::cin, line);
    a = stoll(line);
    getline(std::cin, line);
    line = line.substr(1, line.length() - 2);
    vector<string> ss = splitM(line, ',');
    for (int i = 0; i < ss.size(); i++)
    {
        B.push_back(ss[i][0] - '0');
    }
    cout << getBigExponent();
}