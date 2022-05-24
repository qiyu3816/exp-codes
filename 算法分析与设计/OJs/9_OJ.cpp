#include <iostream>
#include <vector>
#include <string>
#include <stack>

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
    stack<string> st;
    vector<string> res;
    while(true)
    {
        getline(std::cin, line);
        ss = splitM(line, ' ');
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
        while(!st.empty())
        {
            res.push_back(st.top());
            st.pop();
        }
        break;
    }
    for(auto s:res)
    {
        cout << s << " ";
    }
}