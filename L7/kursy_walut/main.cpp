#include <algorithm>
#include <fstream>
#include <iostream>
#include <map>
#include <regex>
#include <sstream>
#include <vector>
using namespace std;

int main()
{
    map<string, float> rates;
    fstream file("/home/piotr/Downloads/Kursy walut - tabela A _ Narodowy Bank Polski - "
                 "Internetowy Serwis Informacyjny.html",
                 ios::in);
    if (file.is_open()) {
        stringstream str;
        str << file.rdbuf();
        string text = str.str();
        std::smatch result;
        std::regex reg(R"(<td>(\d+) ([A-Z]{3})<\/td><td>(\d,\d+)<\/td>)");
        while (std::regex_search(text, result, reg)) {
            // for (auto el : result) {
            //     cout << el << endl;
            // }
            string ex_rate_str = result[3];
            ex_rate_str[1] = '.';
            float ex_rate_tmp = stof(ex_rate_str);
            int units = stoi(result[1]);
            rates[result[2]] = ex_rate_tmp / units;
            text = result.suffix();
        }
        for (auto &el : rates) {
            cout << el.first << " - " << el.second << endl;
        }

        cout << "USD: " << rates["USD"] << endl;
    }
    return 0;
}
