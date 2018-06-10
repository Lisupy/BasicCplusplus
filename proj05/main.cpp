#include <iostream>
#include "cipher.cpp"

int main(){
    std::cout << CreateSquare("squarecipher") << std::endl;
    std::cout << EncodeString("funfast", "squarecipher") << std::endl;
}
