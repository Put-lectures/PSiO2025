#include <fstream>
#include <iostream>
#include <vector>
#include <cmath>
bool is_prime(int n){
    for(int i=2; i<=sqrt(n);i++){

        if(n%i==0){
            return false;
        }
    }
    return true;
}
int words_counter(std::string s){
    int counter=1;

    if (s.size()==0){
        return 0;
    }
    for(int i=0; i<s.size();i++){
        if(s[i]==' '){
            counter++;
        }
    }
    return counter;
}

float accumulate(int n){
    float acc=0;
    for(int i=1;i<n;i++)
    {
        acc+=4*pow(-1,i-1)/(2.0*i-1);
    }
    return acc;
}
int silnia_rec(int n){
    if(n==0) return 1;
    std::cout << n<<std::endl;
    return silnia_rec(n-1)*n;
}
int main()
{

//   std::cout << accumulate(10000);
//   double silnia = 0;
//   for (double i=0;i<1000000;i++)
//     {
//         silnia+=0.1;
//         // std::cout<<i<<"- "<<silnia<<std::endl;
//     }
//     std::cout.precision(25);
//     std::cout<<0.1;
    std::cout << silnia_rec(10);
    return 1;
  }