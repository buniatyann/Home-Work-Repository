#ifndef GAME_H
#define GAME_H

#include <iostream>
#include <iomanip>
#include <stdlib.h>
#include <vector>

using namespace std;

class Game {
private:
    static const int WIN_NUMBER = 2048; // Tile number winning condition
    static const int BSIZE = 4; // Size of the board 4x4
    static const int PROB_NEW_TILE_4 = 20; // Prob. of a new tile to be 4, instead of 2
    
    int board[BSIZE][BSIZE];  // 2D Board array
    int turn; // Keep track of number of turns
    int score;
    
public:
    Game();

    // Makes a one step of a game given input
    void step(char& input);

    // move() function only moves tiles to a specified direction - 
    // i.e. only fills up empty tiles
    bool move(char& input, bool& valid_step);

    // Combines adjacent tiles if they are equal
    bool combine(char& input, bool& valid_step);

    // Adds new tile over random empty tile
    void add_new_tile();

    // Checks if there exist 2048 tile on the board
    bool check_win_status();

    // Getter
    int get_score();

    // Overloaded "<<" operator for printing the board, turns and score to stdout
    friend ostream& operator<<(ostream& outs, const Game& game);
};


#endif // GAME_H 