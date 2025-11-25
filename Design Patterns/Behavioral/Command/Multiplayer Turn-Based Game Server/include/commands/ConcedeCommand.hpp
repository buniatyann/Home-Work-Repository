#ifndef CONCEDE_COMMAND_HPP
#define CONCEDE_COMMAND_HPP

#include "../Command.hpp"

class ConcedeCommand : public Command {
public:
    explicit ConcedeCommand(int playerId);
    void execute(GameState& state, Player& player) override;
    void undo(GameState& state, Player& player) override;
    std::string getDescription() const override;
    int getPlayerId() const override { return playerId_; }
    bool isValid(const GameState&, const Player&) const override { return true; }

private:
    int playerId_;
};

#endif