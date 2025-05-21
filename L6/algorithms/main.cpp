#include <algorithm>
#include <iostream>
#include <list>
#include <vector>
using namespace std;

bool is_even(const int &el)
{
    return el % 2 == 0;
}

bool above_0(const int &el)
{
    return el > 0;
}

bool by_abs(const int &e1, const int &e2)
{
    return abs(e1) > abs(e2);
}
class Threshold
{
private:
    int th_;

public:
    Threshold(int th = 0)
        : th_(th)
    {}
    bool operator()(const int &el) { return el > th_; }
};

int main()
{
    // vector<int> tab;
    // for (int i = 0; i < 120; i++) {
    //     tab.emplace_back(rand());
    //     cout << i << " - " << tab.size() << " - " << tab.capacity() << endl;
    // }
    list<int> tab = {10, -10, 10, 5, 0, 1, 0, 20, -10};

    int val = count_if(tab.begin(), tab.end(), is_even);
    cout << "liczb parzystych w tablicy: " << val << endl;
    // int th = 5;
    // val = count_if(tab.begin(), tab.end(), [th](const int &el) -> bool { return el > th; });

    Threshold th(4);
    val = count_if(tab.begin(), tab.end(), th);

    cout << "liczb powyzej 0: " << val << endl;
    // tab.sort();
    vector<int> tab_2(tab.begin(), tab.end());
    sort(tab_2.begin(), tab_2.end(), by_abs);

    // vector<int> tab_3;
    // copy(tab_2.begin(), tab_2.end(), back_inserter(tab_3));

    for (auto el : tab_2) {
        cout << el << endl;
    }
    cout << val << endl;

    return 0;
}
