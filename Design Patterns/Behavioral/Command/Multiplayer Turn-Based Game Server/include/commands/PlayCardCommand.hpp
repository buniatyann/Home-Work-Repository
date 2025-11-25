#ifndef PLAY_CARD_COMMAND_HPP
#define PLAY_CARD_COMMAND_HPP

#include "../Command.hpp"
#include "../Player.hpp"

class PlayCardCommand : public Command {
public:
    PlayCardCommand(int playerId, int handIndex);
    void execute(GameState& state, Player& player) override;
    void undo(GameState& state, Player& player) override;
    std::string getDescription() const override;
    int getPlayerId() const override { return playerId_; }
    bool isValid(const GameState& state, const Player& player) const override;

private:
    int playerId_;
    int handIndex_;
    Card playedCard_;
    int oldMana_;
};

#endif // PLAY_CARD_COMMAND_HPP