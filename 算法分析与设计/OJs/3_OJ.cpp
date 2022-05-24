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
    vector<int> pos;
    int res;
    bool initialized = false;
    int i = 0;
    while(true)
    {
        //for(int j = 0; j < pos.size(); j += 2)
        //{
        //    cout << "[" << pos[j] << " " << pos[j + 1] << "] ";
        //}
        //cout << endl;
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
            pos.push_back(stoi(ss[0]));
            pos.push_back(stoi(ss[1]));
            continue;
        } else {
            i++;
            int start = stoi(ss[0]);
            int end = stoi(ss[1]);
            for(int j = 0; j < pos.size(); j += 2)
            {
                if((start >= pos[j] && start <= pos[j + 1]) || (end >= pos[j] && end <= pos[j + 1]) || (start < pos[j] && end > pos[j + 1]))
                {
                    pos[j] = pos[j] < start ? pos[j] : start;
                    pos[j + 1] = pos[j + 1] < end ? end : pos[j + 1];
                    for(int k = j + 2; k < pos.size(); k += 2)
                    {
                        if(pos[j + 1] >= pos[k])
                        {
                            if(pos[j + 1] >= pos[k + 1])
                            {
                                pos.erase(pos.begin() + k + 1);
                                pos.erase(pos.begin() + k);
                                k -= 2;
                                continue;
                            } else {
                                pos[j + 1] = pos[k + 1];
                                pos.erase(pos.begin() + k + 1);
                                pos.erase(pos.begin() + k);
                                k -= 2;
                                break;
                            }
                        }
                        else {
                            break;
                        }
                    }
                    break;
                }

                if(end < pos[0])
                {
                    pos.insert(pos.begin(), end);
                    pos.insert(pos.begin(), start);
                    break;
                }
                if(start > pos[pos.size() - 1])
                {
                    pos.push_back(start);
                    pos.push_back(end);
                    break;
                }
            }
        }
    }
    for(int j = 0; j < pos.size(); j += 2)
    {
        res += (pos[j + 1] - pos[j] + 1);
    }
    cout << M - res;
    return 0;
}
