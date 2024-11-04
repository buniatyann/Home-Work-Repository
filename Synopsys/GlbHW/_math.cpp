#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <stdexcept>


typedef long long ll;

ll helper(int n){
    if(n == 1){
        return 9;
    }

    return 9 * helper(n - 1);
}


ll solution(int n){
    if(n < 2){
        throw std::invalid_argument("Not correct!!!!!!");
    }
    if(n == 2){
        return 81;
    }

    return 8 * helper(n - 1);
}