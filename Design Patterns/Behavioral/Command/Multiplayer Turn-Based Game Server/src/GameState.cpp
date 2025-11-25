#include "../include/GameState.hpp"
#include <iostream>
#include <algorithm>

GameState::GameState() = default;

void GameState::apply(CommandPtr cmd) {
    Player& p = getPlayer(cmd->getPlayerId());
    if (!cmd->isValid(*this, p)) {
        std::cout << "INVALID: " << cmd->getDescription() << "\n";
        return;
    }
    cmd->execute(*this, p);
    history.push(std::move(cmd));
    while (!redoStack.empty()) redoStack.pop();
}

void GameState::undoLast() {
    if (history.empty()) { std::cout << "Nothing to undo!\n"; return; }
    auto cmd = std::move(history.top()); history.pop();
    cmd->undo(*this, getPlayer(cmd->getPlayerId()));
    redoStack.push(std::move(cmd));
}

void GameState::nextTurn() {
    currentPlayerId = (currentPlayerId == 1) ? 2 : 1;
    Player& p = getPlayer(currentPlayerId);
    p.hasTurn = true;
    getPlayer(3 - currentPlayerId).hasTurn = false;
    if (p.maxMana < 10) p.maxMana++;
    p.mana = p.maxMana;
}

void GameState::print() const {
    std::cout << "\n=== TURN " << (history.size() + 1) << " | " 
              << getPlayer(currentPlayerId).name << "'s turn ===\n";
    for (int i = 1; i <= 2; ++i) {
        const Player& p = getPlayer(i);
        std::cout << p.name << " | HP: " << p.health << " | Mana: " << p.mana << "/" << p.maxMana << "\n";
        std::cout << "  Board: ";
        for (const auto& c : p.board) std::cout << c.name << " ";
        std::cout << "\n";
    }
    std::cout << std::string(50, '-') << "\n";
}

void GameState::replay() const {
    std::cout << "\nREPLAYING GAME:\n";
    std::stack<CommandPtr> temp = history;
    std::vector<std::string> moves;
    while (!temp.empty()) {
        moves.push_back(temp.top()->getDescription());
        temp.pop();
    }
    std::reverse(moves.begin(), moves.end());
    for (size_t i = 0; i < moves.size(); ++i)
        std::cout << (i+1) << ". " << moves[i] << "\n";
}

Player& GameState::getPlayer(int id) { return id == 1 ? player1 : player2; }
const Player& GameState::getPlayer(int id) const { return id == 1 ? player1 : player2; }