#include "Ostring.h"



int main(){

    Own::string str1("Ravi ");
    Own::string str2("Ravi ");

    std::cout << str1 << " " << str2 << std::endl;

    Own::string str3;
    str3 = str1 + str2;

    std::cout << std::boolalpha << (str1 == str2) << std::endl;

    std::cout << str3 << std::endl;

    Own::string str4 = Own::concat("Hi ","Hello");

    std::cout << str4 << " " <<str3.subStr(2,5) <<std::endl;


    str4 += str3;
    std::cout << str4 << std::endl;

    str4.insert(str4.length() - 1," Sir");

    std::cout << str4 << std::endl;
}