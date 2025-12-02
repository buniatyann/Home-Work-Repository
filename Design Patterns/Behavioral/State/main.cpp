#include <iostream>
#include <memory>
#include "include/Suspect.hpp"
#include "include/WithTaste.hpp"
#include "include/WithoutTaste.hpp"

int main() {
    auto initialState = std::make_unique<WithoutTaste>();
    Suspect suspect(std::move(initialState));

    suspect.giveControlQuestion();  
    suspect.giveBlame();            
    suspect.giveInfoAbout();        

    return 0;
}
