#include <iostream>
#include <string>

using namespace std;

int main()
{
    string str;
    cin >> str;
    int length = str.size();
    string other = "+-*/";
    string letter = "abcdefghijklmnopqrstuvwxyz";
    string digit = "1234567890";
    if(other.find(str[0]) != std::string::npos && length == 1)
    {
        cout << "valid\n";
        return 0;
    } else if(letter.find(str[0]) != std::string::npos) {
        for(int i = 1; i < length; i++)
        {
            if((letter.find(str[i]) != std::string::npos || digit.find(str[i]) != std::string::npos) && (i != length - 1))
            {
                continue;
            } else if(other.find(str[i]) != std::string::npos && (i == length - 1)) {
                cout << "valid\n";
                return 0;
            } else {
                cout << "invalid\n";
                return 1;
            }
        }
    } else {
        cout << "invalid\n";
        return 1;
    }
}