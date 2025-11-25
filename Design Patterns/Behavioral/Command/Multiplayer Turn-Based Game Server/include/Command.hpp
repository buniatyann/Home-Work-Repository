#ifndef COMMAND_HPP
#define COMMAND_HPP

#include <string>
#include <memory>
#include "GameState.hpp"
#include "Player.hpp"

class GameState;
class Player;

class Command {
public:
    virtual ~Command() = default;
    virtual void execute(GameState& state, Player& executor) = 0;
    virtual void undo(GameState& state, Player& executor) = 0;
    virtual std::string getDescription() const = 0;
    virtual int getPlayerId() const = 0;
    virtual bool isValid(const GameState& state, const Player& player) const = 0;
};

using CommandPtr = std::unique_ptr<Command>;

#endif // COMMAND_HPP