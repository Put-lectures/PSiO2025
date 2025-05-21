#include <cmath>
#include <iostream>
using namespace std;

int main()
{
    cout.precision(15);
    cout << 0.02 + 1000000 - 1000000 - 0.02 << endl;
    cout << 0.02 + 1000000 - 0.02 - 1000000;
    float a, b;
    if (fabs(a - b) < 0.00000001)
        return 0;
}
