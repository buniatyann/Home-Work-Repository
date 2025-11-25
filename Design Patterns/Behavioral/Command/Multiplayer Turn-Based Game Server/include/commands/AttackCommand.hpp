#ifndef ATTACK_COMMAND_HPP
#define ATTACK_COMMAND_HPP

#include "../Command.hpp"
#include "../Player.hpp"
#include "../GameState.hpp"

class AttackCommand : public Command {
public:
    AttackCommand(int playerId, int attackerIdx, int targetIdx);
    void execute(GameState& state, Player& player) override;
    void undo(GameState& state, Player& player) override;
    std::string getDescription() const override;
    int getPlayerId() const override { return playerId_; }
    bool isValid(const GameState& state, const Player& player) const override;

private:
    int playerId_;
    int attackerIdx_;
    int targetIdx_;
    int oldAttackerHealth_;
    int oldTargetHealth_;
};

#endif // ATTACK_COMMAND_HPP