#ifndef CHESS_GAME_HPP
#define CHESS_GAME_HPP

#include <vector>
#include <memory>
#include <stack>
#include "Command.hpp"

class ChessGame {
public:
    ChessGame();
    void executeCommand(std::unique_ptr<Command> cmd);
    void undoLastMove();
    void redoLastMove();
    void printBoard() const;
    void replayGame() const;

private:
    int board[8][8];  // Simplified: 0=empty, 1=P, 2=R, ..., 6=K (white), negative=black
    std::stack<std::unique_ptr<Command>> history_;
    std::stack<std::unique_ptr<Command>> redoStack_;
};

#endif // CHESS_GAME_HPP