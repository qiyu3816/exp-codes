#include <iostream>
#include <stack>
#include <string>
#include <vector>

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
    stack<int> t;
    while(true)
    {
        getline(std::cin, line);
        ss = splitM(line, ' ');
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
        cout << t.top();
        break;
    }
}
