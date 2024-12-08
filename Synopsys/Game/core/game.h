#ifndef GAME_H
#define GAME_H

#define WIN_VALUE 2048

#include "core/subject.h"
#include "core/board.h"

class Board;

class Game : public Subject{
public:
    Game(int dimension);
    ~Game();
    void restart();
    bool isGameOver() const;
    Board* getGameBoard() const;
    void move(Direction dir);
    // returns true if win state,
    // (i.e. there is a tile that has the value as defined in WIN_VALUE)
    bool won() const;
    int getScore() const { return score; }

private:
    Board* board;
    bool gameOver;
    int score;

};

#endif // GAME_H