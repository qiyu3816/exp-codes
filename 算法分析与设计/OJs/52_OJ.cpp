#include <iostream>
#include <string>
#include <vector>

using namespace std;

int main()
{
    string line;
    vector<string> ss;
    while(getline(std::cin, line)) {ss.push_back(line);}
    int a = stoi(ss[0]);
    if(a % 2 == 0)
        cout << "true";
    else
        cout << "false";
}