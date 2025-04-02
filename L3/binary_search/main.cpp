#include <iostream>
#include <vector>
using namespace std;
bool binary_search(vector<int> tab, int el)
{
    int begin = 0, end = tab.size() - 1;
    while (begin <= end) {
        int mid = (begin + end) / 2;
        int v = tab[mid];
        if (v == el) {
            return true;
        }
        if (v > el) {
            end = mid - 1;
        } else {
            begin = mid + 1;
        }
    }
    return false;
}
int main()
{
    vector<int> tab = {-1, 0, 10, 15, 19, 20, 25, 30, 99, 128, 512};
    int el = 510;
    if (binary_search(tab, el)) {
        cout << "element zostal znaleziony" << endl;
    } else {
        cout << "brak elementu" << endl;
    }
    return 0;
}
