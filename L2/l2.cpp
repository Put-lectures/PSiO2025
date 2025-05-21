#include <fstream>
#include <iostream>
#include <vector>
int main()
{

 
 char inp;
 do{
 std::cout << "Czy chcesz konytnuowac (t/n)? ";
 std::cin >> inp;
}while(inp!='t' && inp!='T' && inp!='n' && inp!='N');

    if(inp=='t' || inp=='T')
    {
        std::cout << "Kontynuacja";
    }

 std::fstream f("/home/piotr/workspace/plik.txt", std::ios::in);
 if(f.is_open())
 {
    std::string s;
    std::vector<std::string> v;
    while(std::getline(f,s))
    {
        std::cout<<s<<std::endl;
        v.emplace_back(s);
    }
 }
}