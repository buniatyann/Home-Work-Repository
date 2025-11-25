#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <string>
#include <vector>

struct Card {
    int id;
    std::string name;
    int cost;
    int attack;
    int health;

    Card(int i = 0, std::string n = "", int c = 0, int a = 0, int h = 0)
        : id(i), name(std::move(n)), cost(c), attack(a), health(h) {}
};

class Player {
public:
    int id;
    std::string name;
    int health = 30;
    int mana = 0;
    int maxMana = 0;
    bool hasTurn = false;

    std::vector<Card> hand;
    std::vector<Card> board;

    Player(int i = 0, std::string n = "Player")
        : id(i), name(std::move(n)) {}

    void takeDamage(int dmg) {
        health -= dmg;
        if (health < 0) health = 0;
    }

    bool isAlive() const { return health > 0; }
};

#endif // PLAYER_HPP