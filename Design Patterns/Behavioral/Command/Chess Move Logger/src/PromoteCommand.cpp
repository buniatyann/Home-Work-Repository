#include "../include/PromoteCommand.hpp"
#include "../include/ChessGame.hpp"
#include <iostream>

PromoteCommand::PromoteCommand(ChessGame* game, int x, int y, char newPiece)
    : game_(game), x_(x), y_(y), newPiece_(newPiece), oldPiece_('P') {}

void PromoteCommand::execute() {
    {
    oldPiece_ = game_->getPieceCharAt(x_, y_);
    int newVal = (newPiece_ == 'Q') ? 5 : (newPiece_ == 'R') ? 4 : (newPiece_ == 'B') ? 3 : 2;
    game_->setPieceAt(x_, y_, newVal);
    std::cout << "Pawn promoted to " << newPiece_ << "!\n";
}

void PromoteCommand::undo() {
    game_->setPieceAt(x_, y_, 1); // back to pawn
    std::cout << "Promotion undone\n";
}

std::string PromoteCommand::name() const {
    return std::string("Promotion to ") + newPiece_;
}