#include <iostream>
#include <vector>
#include <string>
#include <cstring>

#define MAX_SIZE 501

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

int size;
vector<int> arr;
int A[MAX_SIZE][MAX_SIZE];

void deleteNumToGetMultipliedNeighbor(int A[][MAX_SIZE])
{
    int j = 0;
	for(int r = 3; r <= size; r ++ )
    {
		for(int i = 1; ; i ++ )
        {
			int j = i + r -1;
			for(int k = i + 1; k <= j - 1; k ++ )
            {
				A[i][j] = max(A[i][j], A[i][k] + A[k][j] + arr[i] * arr[k] * arr[j]);
			}
			if(j >= size) break;
		}
	} 
	cout << A[1][size];
}

int main()
{
    string line;
    cin >> line;
    line = line.substr(1, line.length() - 2);
    vector<string> ss = splitM(line, ',');
    size = ss.size() + 2;
    arr.push_back(1);
    arr.push_back(1);
    for(int i = 0; i < ss.size(); i++)
    {
        arr.push_back(stoi(ss[i]));
    }
    arr.push_back(1);
    memset(A, 0, MAX_SIZE * MAX_SIZE);
    deleteNumToGetMultipliedNeighbor(A);
}