#include "../include/CastleCommand.hpp"
#include "../include/ChessGame.hpp"
#include <iostream>

CastleCommand::CastleCommand(ChessGame* game, Type type) : game_(game), type_(type) {}

void CastleCommand::execute() {
    if (type_ == KINGSIDE) {
        game_->setPieceAt(6, 7, game_->getPieceAt(4, 7)); // King
        game_->setPieceAt(5, 7, game_->getPieceAt(7, 7)); // Rook
        game_->setPieceAt(4, 7, 0);
        game_->setPieceAt(7, 7, 0);
        std::cout << "Executed: O-O (Kingside castling)\n";
    } 
    else {
        game_->setPieceAt(2, 7, game_->getPieceAt(4, 7));
        game_->setPieceAt(3, 7, game_->getPieceAt(0, 7));
        game_->setPieceAt(4, 7, 0);
        game_->setPieceAt(0, 7, 0);
        std::cout << "Executed: O-O-O (Queenside castling)\n";
    }
}

void CastleCommand::undo() {
    if (type_ == KINGSIDE) {
        game_->setPieceAt(4, 7, game_->getPieceAt(6, 7));
        game_->setPieceAt(7, 7, game_->getPieceAt(5, 7));
        game_->setPieceAt(6, 7, 0);
        game_->setPieceAt(5, 7, 0);
    } 
    else {
        game_->setPieceAt(4, 7, game_->getPieceAt(2, 7));
        game_->setPieceAt(0, 7, game_->getPieceAt(3, 7));
        game_->setPieceAt(2, 7, 0);
        game_->setPieceAt(3, 7, 0);
    }
    
    std::cout << "Undid castling\n";
}

std::string CastleCommand::name() const {
    return type_ == KINGSIDE ? "O-O" : "O-O-O";
}