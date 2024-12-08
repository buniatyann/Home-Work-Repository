#include "core/board.h"
// #include "core/tile.h"
#include <iostream>
#include <stdlib.h> // srand, rand
#include <time.h> // time
#include "board.h"
// #include <QDebug>

Board::Board(int dimension)
{
    this->pointsScoredLastRound = 0;
    this->tileCollisionLastRound = false;
    this->dimension = dimension;
    init();
}

Board::Board(const Board &other)
{
    dimension = other.dimension;
    init();
    
    for(int i = 0; i < dimension; ++i){
        for(int j = 0; j < dimension; ++j){
            if(other.board[i][j] = nullptr){
                board[i][j] = nullptr;
            }
            else{
                board[i][j] = new Tile*(other.board[i][j]);
            }
        }
    }
}

Board::~Board()
{
    for(int i = 0; i < this->dimension; ++i){
        for(int j = 0; j < this->dimension; ++j){
            delete board[i][j];
        }
    }
}

void Board::reset()
{
    this->pointsScoredLastRound = 0;
    this->tileCollisionLastRound = false;

    for(int i = 0; i < this->dimension; ++i){
        for(int j = 0; j < this->dimension; ++j){
            delete board[i][j];
            board[i][j] = nullptr;
        }
    }

    QVector<int> start = this->freePosition();
    board[start[0]][start[1]] = new Tile();
    start = this->freePosition();
    board[start[0]][start[1]] = new Tile();
}

Tile *Board::getTile(int i, int j)
{
    return nullptr;
}

void Board::init()
{
    board.resize(dimension);

    for(int i = 0; i < dimension; ++i){
        board[i].resize(dimension);
    }

    for(int i = 0; i < dimension; ++i){
        for(int j = 0; j < dimension; ++j){
            board[i][j] = nullptr;
        }
    }
}

QVector<int> Board::freePosition()
{
    QVector<int> pos;

    if(this->full()){
        pos.append(-1);
        pos.append(-1);
    }
    else{
        int i, j;

        do{
            i = rand() % this->dimension;
            j = rand() % this->dimension;
        }
        while(board[i][j] != nullptr);
        
        pos.append(i);
        pos.append(j);
    }

    return pos;
}

bool Board::changed(Board &other) const
{
    if(this->dimension != other.dimension){
        return false;
    }

    for(int i = 0; i < this->dimension; ++i){
        for(int j = 0; j < this->dimension; ++j){
            if( ( (this->board[i][j] == nullptr && other.board[i][j] != nullptr) ||
                (this->board[i][j] != nullptr && other.board[i][j] == nullptr) ) ||
                ((this->board[i][j] != nullptr && other.board[i][j] != nullptr) &&
                this->board[i][j]->getVlaue() != other.board[i][j]->getVlaue())
            )
            {
                return true;
            }
        }
    }

    return false;
}
