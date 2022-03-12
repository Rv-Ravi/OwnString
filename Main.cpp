#include "Ostring.h"


int main(){
    Own::string str1("hello");
    Own::string str2("Friends");

    std::cout << str1 << " " << str2 << std::endl;

    Own::string str3;
    str3 = str1 + str2;

    std::cout << str3 << std::endl;

    Own::string str4 = Own::concat("Hi ","Hello");

    std::cout << str4 << " " <<str3.subStr(2,5,true) <<std::endl;


    str4 += str3;
    std::cout << str4 << std::endl;
}