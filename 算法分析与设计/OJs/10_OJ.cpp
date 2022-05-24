#include <iostream>
#include <string>
#include <unordered_map>

using namespace std;

string getMinCoverSubstr(string s, string t)
{
    string res = "";
    if(s.length() < t.length() || s.empty() || t.empty())
    {
        return res;
    }
    
    unordered_map<char, int> sm;
    unordered_map<char, int> st;
    for(int i = 0; i < t.length(); i++)
    {
        if(st.find(t[i]) != st.end())
        {
            ++st[t[i]];
        } else {
            st.emplace(t[i], 1);
        }
    }
    int length = 1000000, leftAns = 0;
    int left = -1, right = -1;
    
    while(++left < s.length() - st.size() + 1)
    {
        // cout << "left " << left << endl;
        right = left - 1;
        sm.clear();
        while(++right < s.length())
        {
            if(st.find(s[right]) != st.end())
            {
                // cout << "find " << s[right] << " " << right << endl;
                if(sm.find(s[right]) != sm.end())
                {
                    ++sm[s[right]];
                } else {
                    sm.emplace(s[right], 1);
                }
                if(sm.size() >= st.size())
                {
                    bool enough = true;
                    for(auto a:sm)
                    {
                        if(st[a.first] > a.second)
                        {
                            enough = false;
                            break;
                        }
                    }
                    if(enough)
                    {
                        if(length > right - left + 1)
                        {
                            length = right - left + 1;
                            leftAns = left;
                        }
                        // cout << "length&ans " << length << " " << leftAns << endl;
                        break;
                    }
                }
            }
        }
    }
    // cout << "length: " << length << endl;
    return length == 1000000 ? res : s.substr(leftAns, length);
}

int main()
{
    string a, b;
    getline(std::cin, a);
    getline(std::cin, b);
    cout << getMinCoverSubstr(a, b);
    // unordered_map<char, int> test;
    // test.emplace('s', 1);
    // test.emplace('s', 3);
    // test.emplace('s', 4);
    // test.emplace('t', 3);
    // cout << test.size() << endl;
    // test.erase(test.find('s'));
    // for(auto s:test)
    // {
    //     cout << s.first << " " << s.second << std::endl;
    // }
}