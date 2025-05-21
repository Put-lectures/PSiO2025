#include <iostream>

using namespace std;
struct sOsoba
{
    char imie_nazwisko[25];
    int wiek;
    char plec;
};

int main()
{
    sOsoba studenci[50];
    for (int i = 0; i < 3; i++) {
        cout << "podaj imie i nazwisko: ";
        cin.getline(studenci[i].imie_nazwisko, 25);
        cout << "podej wiek:";
        cin >> studenci[i].wiek;
        cout << "podaj plec: ";
        cin >> studenci[i].plec;
        cin.ignore();
    }

    return 0;
}
