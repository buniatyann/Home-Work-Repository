#include "../include/commands/AttackCommand.hpp"
#include <iostream>

AttackCommand::AttackCommand(int playerId, int attackerIdx, int targetIdx)
    : playerId_(playerId), attackerIdx_(attackerIdx), targetIdx_(targetIdx) {}

void AttackCommand::execute(GameState& state, Player& player) {
    Player& opponent = state.getPlayer(3 - playerId_);
    Card& attacker = player.board[attackerIdx_];
    Card& target = opponent.board[targetIdx_];

    oldAttackerHealth_ = attacker.health;
    oldTargetHealth_ = target.health;

    attacker.health -= target.attack;
    target.health -= attacker.attack;

    std::cout << player.name << "'s " << attacker.name << " attacks " 
              << opponent.name << "'s " << target.name << "!\n";

    if (attacker.health <= 0) 
        std::cout << attacker.name << " died!\n";
    if (target.health <= 0) 
        std::cout << target.name << " died!\n";
}

void AttackCommand::undo(GameState& state, Player& player) {
    player.board[attackerIdx_].health = oldAttackerHealth_;
    state.getPlayer(3 - playerId_).board[targetIdx_].health = oldTargetHealth_;
    std::cout << "UNDO: Attack reversed\n";
}

std::string AttackCommand::getDescription() const {
    return playerId_ == 1 ? "Alice attacked" : "Bob attacked";
}

bool AttackCommand::isValid(const GameState& state, const Player& player) const {
    if (!player.hasTurn) 
        return false;

    if (attackerIdx_ >= (int)player.board.size()) 
        return false;
        
    Player& opponent = state.getPlayer(3 - playerId_);
    return targetIdx_ >= 0 && targetIdx_ < (int)opponent.board.size();
}