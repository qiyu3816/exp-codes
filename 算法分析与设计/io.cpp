#include <iostream>
#include <string>
#include <vector>
#define INT_MAX 2147483647
#define INT_MIN (-INT_MAX - 1)

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


int main(int argc, char** argv)
{
    /**
     * string.find()
     * string.substr()
     */
    // string line = "01234555556789";
    // size_t pos = line.find('5');
    // std::cout << line.substr(0, pos) << "\n";

    /**
     * getline() 接收空格 不接收回车
     * splitM()
     */
    // string line;
    // vector<string> ss;
    // while(true)
    // {
    //     getline(std::cin, line);
    //     std::cout << "fuck you said " << line << "\n";
    //     ss = splitM(line, ' ');
    //     int a = 0;
    //     for(auto s:ss)
    //     {
    //         a++;
    //         std::cout << a << "fuck " << s << "\n";
    //     }
    //     if(line == "fuck")
    //         break;
    // }

    /**
     * cin >> char[] 不接收空格不接收回车 输入比数组短则空余部分不修改(可能乱码) 输入比数组长则多余部分不输入
     */
    // char c[10];
    // cin >> c;
    // for(int i = 0; i < 10; i++)
    //     cout << c[i];
    // cout << endl;

    /**
     * gets() 与cin >> char[]的区别在于gets()接收空格
     */
    // char cs[10];
    // gets(cs);
    // for(int i = 0; i < 10; i++)
    //     cout << cs[i];
    // cout << endl;

    /**
     * getchar() 接收空格和换行符
     */
    char cc[10];
    for(int i = 0; i < 10; i++)
        cc[i] = getchar();
    cout << "Your input:\n";
    for(int i = 0; i < 10; i++)
        cout << cc[i];
    cout << endl;
}
