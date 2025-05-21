#include <algorithm>
#include <fstream>
#include <iostream>
#include <map>
#include <unordered_map>
#include <vector>
using namespace std;

int main()
{
    unordered_map<string, int> tree;
    fstream file("gpl-3.0.txt", ios::in);
    if (file.is_open()) {
        while (!file.eof()) {
            string word;
            file >> word;
            tree[word]++;
        }
    }
    vector<pair<string, int>> words_counter(tree.begin(), tree.end());

    sort(words_counter.begin(),
         words_counter.end(),
         [](const pair<string, int> &el1, const pair<string, int> &el2) {
             if (el1.second == el2.second)
                 return el1.first < el2.first;
             else
                 return el1.second < el2.second;
         });
    for (auto &el : words_counter) {
        cout << el.first << " - " << el.second << endl;
    }
    return 0;
}
