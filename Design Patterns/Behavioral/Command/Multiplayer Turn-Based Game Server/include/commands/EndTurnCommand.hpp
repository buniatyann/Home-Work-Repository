#ifndef END_TURN_COMMAND_HPP
#define END_TURN_COMMAND_HPP

#include "../Command.hpp"
#include "../Player.hpp"
#include "../GameState.hpp"

class EndTurnCommand : public Command {
public:
    explicit EndTurnCommand(int playerId);
    void execute(GameState& state, Player& player) override;
    void undo(GameState& state, Player& player) override;
    std::string getDescription() const override;
    int getPlayerId() const override { return playerId_; }
    bool isValid(const GameState&, const Player& player) const override;

private:
    int playerId_;
};

#endif // END_TURN_COMMAND_HPP