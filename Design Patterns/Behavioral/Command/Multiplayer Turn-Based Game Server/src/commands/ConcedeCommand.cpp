#include "../include/commands/ConcedeCommand.hpp"
#include <iostream>

ConcedeCommand::ConcedeCommand(int playerId) : playerId_(playerId) {}

void ConcedeCommand::execute(GameState& state, Player& player) {
    std::cout << "GAME OVER! " << player.name << " has CONCEDED!\n";
}

void ConcedeCommand::undo(GameState&, Player&) {
    std::cout << "Concede undone — game continues!\n";
}

std::string ConcedeCommand::getDescription() const {
    return playerId_ == 1 ? "Alice conceded" : "Bob conceded";
}