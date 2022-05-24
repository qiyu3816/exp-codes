// 第一行输入题库题数M 学生人数N
// 后N行每行输入学生做了的题的题号
// 输出学生没做的题的数量
#include <iostream>
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
    int M = 0, N = 0;
    vector<int> res;
    bool initialized = false;
    int i = 0;
    while(true)
    {
        if(i == N && i != 0)
            break;
        getline(std::cin, line);
        ss = splitM(line, ' ');
        if(!initialized)
        {
            initialized = true;
            M = stoi(ss[0]);
            N = stoi(ss[1]);
            if(M == 0 || N == 0)
            {
                break;
            }
            continue;
        }
        if(i == 0)
        {
            i++;
            for(int j = 0; j < ss.size(); j++)
            {
                res.push_back(stoi(ss[j]));
            }
            continue;
        } else {
            i++;
            int k = 0;
            for(int j = 0; j < ss.size(); j++)
            {
                int tmp = stoi(ss[j]);
                for(; k < res.size() && res[k] < tmp; k++) {}
                if(k < res.size())
                {
                    if(res[k] != tmp)
                        res.insert(res.begin() + k, tmp);
                } else if(k == res.size()) {
                    res.push_back(tmp);
                }
            }
        }
    }
    cout << M - res.size();
    return 0;
}
