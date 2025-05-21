#include <iostream>
using namespace std;
int main(){
    // char inp;
    // cout<<"Czy chcesz kontynuowac (t/n)? ";
    // cin >> inp;

    // if(inp=='t' || inp=='T'){
    //     cout << "Kontynuacja";
    // }
    // cout<< "podaj liczbe nie podzielna przez 5";
    // int i;
    // cin >> i;
    // if(i%5!=0){

    // }

    cout<<"1-zrob cos, 2- oblicz silnie, 3- wyjdz";
    char inp;
    cin >> inp;
    switch(inp){
        case '1:{
            int a;
            a=5; 
            cout << "co mam zrobic?"<<endl;
        }
        case 2:{

            cout<<"Licze silnie"<<endl;
    }
        case 3:
            cout<< "wyjscie"<<endl;
        
        
    }
}