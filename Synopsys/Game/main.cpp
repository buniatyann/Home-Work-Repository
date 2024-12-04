#include <iostream>
#include <stdlib.h>
#include <ctime>
#include "game.h"


int main() {
    std::cout << "HI! WELCOME TO '2048' GAME!" << std::endl
         << "Your goal is to reach 2048 on any tile." << std::endl
         << "Use keys 'w','a','s','d' to move tiles up, left, down, right respectively" << std::endl
         << "Good luck and don't get stuck in an unmovable board!" << std::endl;
    
    srand(time(NULL));
    Game game;
    std::cout << game;
    char input;
    std::cin >> input;
    
    while (input != '.') {
        game.step(input);
        std::cout << game;

        if (game.check_win_status()) {
            std::cout << "Congratualtions! You have won!" << std::endl
                 << "You final score is: " << game.get_score() << std::endl;
            
            return 0;
        }
        
        std::cin >> input;
    }

    return 0;
}