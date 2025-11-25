#include "../include/MoveCommand.hpp"
#include "../include/ChessGame.hpp"
#include <iostream>
#include <sstream>

MoveCommand::MoveCommand(ChessGame* game, int fromX, int fromY, int toX, int toY)
    : game_(game), fromX_(fromX), fromY_(fromY), toX_(toX), toY_(toY), capturedPiece_(-1) {
    std::ostringstream oss;
    oss << char('a' + fromX) << (8 - fromY)
        << char('a' + toX)   << (8 - toY);
    notation_ = oss.str();
}

void MoveCommand::execute() {
    capturedPiece_ = game_->getPieceAt(toX_, toY_);

    int piece = game_->getPieceAt(fromX_, fromY_);
    game_->setPieceAt(toX_, toY_, piece);
    game_->setPieceAt(fromX_, fromY_, 0);

    std::std::cout << "Executed move: " << notation_ << "\n";
}

void MoveCommand::undo() {
    int piece = game_->getPieceAt(toX_, toY_);
    game_->setPieceAt(fromX_, fromY_, piece);
    game_->setPieceAt(toX_, toY_, capturedPiece_);

    std::cout << "Undid move: " << notation_ << "\n";
}