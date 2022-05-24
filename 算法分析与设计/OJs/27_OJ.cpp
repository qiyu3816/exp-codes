#include <iostream>
#include <vector>
#include <string>
#include <stack>
#include <cmath>

using namespace std;

// 把没有空格的计算式元素分解存入vector
std::vector<std::string> getCalculateElementsWithoutSpace(string s)
{
    std::vector<std::string> res;
    if(s.empty()) return res;
    std::string tmp;
    int num = 0;
    bool numbering = false;
    for(int i = 0; i < s.size(); i++)
    {
        char c = s[i];
        if(c == '(' || c == ')' || c == '+' || c == '-' || c == '*' || c == '/')
        {
            if(numbering)
            {
                res.push_back(to_string(num));
                numbering = false;
            }
            num = 0;
            tmp = c;
            res.push_back(tmp);
        } else {
            numbering = true;
            num = num * 10 + (c - '0');
        }
    }
    if(num != 0)
        res.push_back(to_string(num));
    return res;
}

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

// 中缀变后缀
vector<string> middix2suffix(vector<string> &ss)
{
    vector<string> res;
    stack<string> st;
    for(auto s:ss)
    {
        if(s == "*" || s == "/")
        {
            if(st.empty())
            {
                st.push(s);
            } else {
                while(!st.empty() && st.top() != "+" && st.top() != "-" && st.top() != "(")
                {
                    res.push_back(st.top());
                    st.pop();
                }
                st.push(s);
            }
        } else if(s == "+" || s == "-") {
            if(st.empty())
            {
                st.push(s);
            } else {
                while(!st.empty() && st.top() != "(")
                {
                    res.push_back(st.top());
                    st.pop();
                }
                st.push(s);
            }
        } else if(s == "(") {
            st.push(s);
        } else if(s == ")") {
            while(st.top() != "(")
            {
                res.push_back(st.top());
                st.pop();
            }
            st.pop();
        } else {
            res.push_back(s);
        }
    }
    // 如果必要 这一步stack转vector可以省略
    while(!st.empty())
    {
        res.push_back(st.top());
        st.pop();
    }
    return res;
}

// 后缀表达式计算结果
int suffixCalculate(vector<string> &ss)
{
    stack<int> t;
    for(int i = 0; i < ss.size(); i++)
    {
        char tmp = '?';
        if(ss[i] == "+" || ss[i] == "-" || ss[i] == "*" || ss[i] == "/")
        {
            tmp = ss[i][0];
        }
        switch(tmp)
        {
            case '+':
            {
                int top = t.top();
                t.pop();
                int down = t.top();
                t.pop();
                t.push(down + top);
                break;
            }
            case '-':
            {
                int top = t.top();
                t.pop();
                int down = t.top();
                t.pop();
                t.push(down - top);
                break;
            }
            case '*':
            {
                int top = t.top();
                t.pop();
                int down = t.top();
                t.pop();
                t.push(down * top);
                break;
            }
            case '/':
            {
                int top = t.top();
                t.pop();
                int down = t.top();
                t.pop();
                t.push(down / top);
                break;
            }
            default:
            {
                t.push(stoi(ss[i]));
                break;
            }
        }
    }
    return t.top();
}

// 没有乘除的计算式直接计算结果
int calculateAddSubtractWithoutSpace(string s)
{
    stack<int> t;
    t.push(1);
    int sign = 1;
    int res = 0;
    int n = s.length();

    int i = 0;
    while (i < n)
    {
        if (s[i] == ' ') {
            i++;
        } else if (s[i] == '+') {
            sign = t.top();
            i++;
        } else if (s[i] == '-') {
            sign = -t.top();
            i++;
        } else if (s[i] == '(') {
            t.push(sign);
            i++;
        } else if (s[i] == ')') {
            t.pop();
            i++;
        } else {
            long num = 0;
            while (i < n && s[i] >= '0' && s[i] <= '9')
            {
                num = num * 10 + s[i] - '0';
                i++;
            }
            res += sign * num;
        }
    }
    return res;
}

int main()
{
    string line;
    getline(std::cin, line);
    cout << calculateAddSubtractWithoutSpace(line);
}