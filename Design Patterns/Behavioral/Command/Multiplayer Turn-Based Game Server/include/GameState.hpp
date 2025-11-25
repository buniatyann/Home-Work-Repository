#ifndef GAME_STATE_HPP
#define GAME_STATE_HPP

#include "Player.hpp"
#include "Command.hpp"
#include <stack>
#include <memory>

class GameState {
public:
    GameState();

    void apply(CommandPtr cmd);
    void undoLast();
    void nextTurn();
    void print() const;
    void replay() const;

    Player& getPlayer(int id);
    const Player& getPlayer(int id) const;
    int getCurrentTurn() const { return currentPlayerId; }

private:
    Player player1{1, "Alice"};
    Player player2{2, "Bob"};
    int currentPlayerId = 1;

    std::stack<CommandPtr> history;
    std::stack<CommandPtr> redoStack;
};

#endif // GAME_STATE_HPP