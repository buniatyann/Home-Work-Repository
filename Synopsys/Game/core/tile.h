#ifndef TILE_H
#define TILE_H

#define EXP_MULTIPLIER 2

class Tile
{
public:
    Tile();
    Tile(const Tile& other);
    Tile(int value);
    int getValue() const;
    void upgrade();
    void setUpgratedThisMove(bool updated);
    bool getUpgratedThisMove() const;

private:
    int value;
    bool upgratedThisMove;
};

#endif // TILE_H