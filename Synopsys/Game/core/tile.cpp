#include "tile.h"

Tile::Tile()
{
    value = 2; upgratedThisMove = false; 
}

Tile::Tile(const Tile &other)
{
    this->value = other.value;   
}

Tile::Tile(int value)
{
    this->value = value;
}

int Tile::getValue() const
{
    return this->value;
}

void Tile::upgrade()
{
    value *= EXP_MULTIPLIER;
}

void Tile::setUpgratedThisMove(bool updated)
{
    this->upgratedThisMove = updated;
}

bool Tile::getUpgratedThisMove() const
{
    return this->upgratedThisMove;
}
