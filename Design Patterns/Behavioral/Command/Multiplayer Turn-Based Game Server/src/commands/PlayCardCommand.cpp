#include "../include/commands/PlayCardCommand.hpp"
#include <iostream>

PlayCardCommand::PlayCardCommand(int playerId, int handIndex)
    : playerId_(playerId), handIndex_(handIndex) {}

void PlayCardCommand::execute(GameState& state, Player& player) {
    playedCard_ = player.hand[handIndex_];
    oldMana_ = player.mana;
    player.mana -= playedCard_.cost;
    player.hand.erase(player.hand.begin() + handIndex_);
    player.board.push_back(playedCard_);
    std::cout << player.name << " played " << playedCard_.name 
              << " (Cost: " << playedCard_.cost << ", Mana left: " << player.mana << ")\n";
}

void PlayCardCommand::undo(GameState& state, Player& player) {
    player.mana = oldMana_;
    player.hand.push_back(playedCard_);
    player.board.pop_back();
    std::cout << "UNDO: " << player.name << " returned " << playedCard_.name << " to hand\n";
}

std::string PlayCardCommand::getDescription() const {
    return playerId_ == 1 ? "Alice played " + playedCard_.name 
                          : "Bob played " + playedCard_.name;
}

bool PlayCardCommand::isValid(const GameState&, const Player& player) const {
    return player.hasTurn &&
           handIndex_ >= 0 && handIndex_ < (int)player.hand.size() &&
           player.mana >= player.hand[handIndex_].cost;
}