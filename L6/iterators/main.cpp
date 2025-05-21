#include <iostream>
#include <list>
#include <vector>

using namespace std;
struct sPoint
{
    float x;
    float y;
};

int main()
{
    vector<int> tab = {1, 5, 0, 7, 3, 3, 3, 7, 0, 10};
    sPoint p;
    p.x = 5;
    pair<float, float> p2;
    p2.first = 0;
    // for (int i = 0; i < tab.size(); i++) {
    //     tab[i] = rand()%100;
    // }
    for (auto itr = tab.begin(); itr != tab.end();) {
        if (*itr == 0) {
            itr = tab.emplace(itr, -99);
            itr++;
        }
        if (*itr == 3) {
            itr = tab.erase(itr);
        } else {
            ++itr;
        }
    }

    for (auto &el : tab) {
        cout << el << endl;
    }

    return 0;
}
