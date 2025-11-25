#include "../include/commands/UseHeroPowerCommand.hpp"
#include <iostream>

UseHeroPowerCommand::UseHeroPowerCommand(int playerId) : playerId_(playerId) {}

void UseHeroPowerCommand::execute(GameState& state, Player& player) {
    oldMana_ = player.mana;
    oldOpponentHealth_ = state.getPlayer(3 - playerId_).health;
    player.mana -= 2;
    state.getPlayer(3 - playerId_).takeDamage(2);
    std::cout << player.name << " used Hero Power! Deals 2 damage!\n";
}

void UseHeroPowerCommand::undo(GameState& state, Player& player) {
    player.mana = oldMana_;
    state.getPlayer(3 - playerId_).health = oldOpponentHealth_;
}

std::string UseHeroPowerCommand::getDescription() const {
    return playerId_ == 1 ? "Alice used Hero Power" : "Bob used Hero Power";
}

bool UseHeroPowerCommand::isValid(const GameState&, const Player& player) const {
    return player.hasTurn && player.mana >= 2;
}