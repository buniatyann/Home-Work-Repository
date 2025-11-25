#include <iostream>
#include "ChessGame.hpp"
#include "MoveCommand.hpp"
#include "CastleCommand.hpp"
#include "PromoteCommand.hpp"

int main() {
    std::cout << "CHESS MOVE LOGGER - Command Pattern\n\n";
    ChessGame game;

    // (Anderssen vs Kieseritzky, 1851)
    game.executeCommand(std::make_unique<MoveCommand>(&game, 4,1,4,3)); // e2-e4
    game.executeCommand(std::make_unique<MoveCommand>(&game, 4,6,4,4)); // e7-e5
    game.executeCommand(std::make_unique<MoveCommand>(&game, 5,0,2,3)); // Qf3
    game.executeCommand(std::make_unique<MoveCommand>(&game, 1,6,2,4)); // Nc6
    game.executeCommand(std::make_unique<MoveCommand>(&game, 6,0,5,1)); // Nf2??

    std::cout << "\nAfter 5 moves:\n";
    game.printBoard();

    std::cout << "\nUNDO last 3 moves...\n";
    game.undoLastMove();
    game.undoLastMove();
    game.undoLastMove();

    std::cout << "\nREDO all moves...\n";
    game.redoLastMove();
    game.redoLastMove();
    game.redoLastMove();

    std::cout << "\nREPLAY ENTIRE GAME:\n";
    game.replayGame();

    return 0;
}