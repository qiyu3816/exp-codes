#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

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

struct fraction
{
    double val;
    int u, d;
    fraction() {}
    fraction(double x, int y, int z) : val(x), u(y), d(z) {}
    bool operator<(const fraction &other) const { return val < other.val; }
    bool operator>(const fraction &other) const { return val > other.val; }
};

vector<int> nums;
int n, k;

void KthLeastFraction()
{
    vector<fraction> fractions;
    for (int i = 0; i < n; i++)
    {
        for(int j = i + 1; j < n; j++)
        {
            fraction f;
            double a = nums[i], b = nums[j];
            double v = a / b;
            f.val = v, f.u = nums[i], f.d = nums[j];
            fractions.push_back(f);
        }
    }

    sort(fractions.begin(), fractions.end());
    cout << fractions[k - 1].u << "," << fractions[k - 1].d;
}

int main()
{
    string line;
    getline(std::cin, line);
    cin >> k;
    vector<string> ss = splitM(line, ',');
    n = ss.size();
    nums.resize(n);
    for (int i = 0; i < n; i++)
    {
        nums[i] = stoi(ss[i]);
    }
    KthLeastFraction();
}