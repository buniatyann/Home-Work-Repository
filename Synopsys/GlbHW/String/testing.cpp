#include <iostream>
#include <string>

int main(){
    double k = 1.97;
    auto m = static_cast<int>(k);

    std::cout << m << ' ';
    std::cout << k;

    return 0;
}