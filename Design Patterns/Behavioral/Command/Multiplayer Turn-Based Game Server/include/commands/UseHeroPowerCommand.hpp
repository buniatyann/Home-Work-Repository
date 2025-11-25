#ifndef USE_HERO_POWER_COMMAND_HPP
#define USE_HERO_POWER_COMMAND_HPP

#include "../Command.hpp"

class UseHeroPowerCommand : public Command {
public:
    explicit UseHeroPowerCommand(int playerId);
    void execute(GameState& state, Player& player) override;
    void undo(GameState& state, Player& player) override;
    std::string getDescription() const override;
    int getPlayerId() const override { return playerId_; }
    bool isValid(const GameState&, const Player& player) const override;

private:
    int playerId_;
    int oldMana_;
    int oldOpponentHealth_;
};

#endif