#include <iostream>
#include <string>
#include <stack>

using namespace std;

string static cloneStr(int n, string s)
{
    string res = "";
    for(int i = 0; i < n; i++)
    {
        res += s;
    }
    return res;
}

void printEncoded(string s)
{
    string res = "";
    stack<string> st;
    int length = s.length();
    for(int i = 0; i < length; i++)
    {
        if(s[i] == '[')
        {
            string str = "";
            str.push_back(s[i]);
            st.push(str);
        } else if(s[i] == ']') {
            string str = "";
            str += st.top();
            st.pop(); // str
            st.pop(); // "["
            int num = stoi(st.top());
            st.pop(); // num
            string u = "";
            if(st.empty())
            {
                u += cloneStr(num, str);
            } else if(st.top()[0] != '[' && (st.top()[0] < '0' || st.top()[0] > '9')) {
                u = st.top();
                st.pop(); // last
                u += cloneStr(num, str);
            }
            st.push(u);
        } else if(s[i] >= '0' && s[i] <= '9') {
            string num = "";
            while(i < length && s[i] >= '0' && s[i] <= '9')
            {
                num.push_back(s[i]);
                i++;
            }
            st.push(num);
            i--;
        } else {
            string str = "";
            while(i < length && s[i] != '[' && s[i] != ']' && (s[i] < '0' || s[i] > '9'))
            {
                str.push_back(s[i]);
                i++;
            }
            if(st.empty())
            {
                st.push(str);
            } else if(st.top()[0] != '[' && (st.top()[0] < '0' || st.top()[0] > '9')) {
                string u = st.top();
                st.pop();
                u += str;
                st.push(u);
            } else {
                st.push(str);
            }
            i--;
        }
    }
    res = st.top();
    cout << res;
}

int main()
{
    string line;
    getline(std::cin, line);
    printEncoded(line);
}