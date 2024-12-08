#ifndef BOARD_H
#define BOARD_H

// #include "core/subject.h"
// #include <QString>
// #include <QVector>

class Tile;

enum Direction { UP, DOWN, LEFT, RIGHT };

class Board : public Subject {
public:
    Board(int dimension);
    Board(const Board& other);

    ~Board();

    void reset();
    void move(Direction direction);
    Tile* getTile(int i, int j);
    int getDimension() const;
    bool full() const;
    int getPointsScoredLastRound() const;
    bool isTileCollisionLastRound() const;
    bool movePossible() const;

private:
    QVector<QVector<Tile*>> board;
    int dimension;
    int pointsScoredLastRound;
    bool tileCollisionLastRound;
    // empty board creation
    void init();
    // generate a random, free position on the board
    QVector<int> freePosition();
    // return true if the current state of the board is different from the argument 
    bool changed(Board& other) const;
    bool inbounds(int i, int j);

    void moveHorizontally(int i, int j, Direction dir);
    void moveVertically(int i, int j, Direction dir);
    void handleCollision(int i, int j);

    // reinitialization for the next round
    void prepareForNextRound();
}

#endif // BOARD_H