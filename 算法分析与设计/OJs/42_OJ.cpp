#include <iostream>
#include <string>
#include <vector>

using namespace std;

void ifHavaRelation(string a, string b)
{
    int size1 = a.length(), size2 = b.length();
    int recordA = 0, recordB = 0, equals = 0;
    for(; recordA < size1; recordA++)
    {
        for(; recordB < size2; recordB++)
        {
            if(a[recordA] == b[recordB])
            {
                recordB++;
                equals++;
                break;
            }
        }
    }
    cout << (equals == size1 ? "true" : "false");
}

int main()
{
    string a, b;
    getline(std::cin, a);
    getline(std::cin, b);
    ifHavaRelation(a, b);
}