#include <iostream>
#include <cmath>

using namespace std;

int main(int argc, char** argv)
{
    float R = 6371000.f;
    float PI = 3.141592653f;
    int n = 5;
    float points[][4] = {
        {90.0, 30.0, 90.0, 31.0},
        {90.0, 31.0, 180.0, 90.0},
        {180.0, 90.0, 180.0, 30.0},
        {180.0, 30.0, 0.0, 31.0},
        {0.0, 31.0, 0.0, 90.0},
    };
    float x, y, d = 0.f;
    for(int i = 0; i < n; i++)
    {
        x = R * cos((points[i][1] + points[i][3]) * PI / 360.f) * PI * (points[i][0] - points[i][2]) / 180.f;
        y = R * (points[i][1] - points[i][3]) * PI / 180.f;
        d += sqrt(x * x + y * y);
        cout << d << endl;
    }
}