#include <iostream>
#include <vector>
using namespace std;

int main()
{
    //tablica
    vector<int> tab = {-10, -100, 29, 36, 1, 0};
    int rozmiar = tab.size();
    bool przestawiono;
    do {
        rozmiar--;
        przestawiono = false;
        for (int i = 0; i < rozmiar; i++) {
            if (tab[i] > tab[i + 1]) {
                int tmp = tab[i];
                tab[i] = tab[i + 1];
                tab[i + 1] = tmp;
                przestawiono = true;
            }
        }
    } while (przestawiono);

    for (int i = 0; i < tab.size(); i++) {
        cout << tab[i] << endl;
    }
    return 0;
}
