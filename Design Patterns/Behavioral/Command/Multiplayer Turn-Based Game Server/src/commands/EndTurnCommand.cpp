#include "../include/commands/EndTurnCommand.hpp"
#include <iostream>

EndTurnCommand::EndTurnCommand(int playerId) : playerId_(playerId) {}

void EndTurnCommand::execute(GameState& state, Player& player) {
    player.hasTurn = false;
    state.nextTurn();
    std::cout << player.name << " ended their turn\n";
}

void EndTurnCommand::undo(GameState& state, Player& player) {
    state.nextTurn(); state.nextTurn(); // go back 2 turns
    player.hasTurn = true;
}

std::string EndTurnCommand::getDescription() const {
    return playerId_ == 1 ? "Alice ended turn" : "Bob ended turn";
}

bool EndTurnCommand::isValid(const GameState&, const Player& player) const {
    return player.hasTurn;
}