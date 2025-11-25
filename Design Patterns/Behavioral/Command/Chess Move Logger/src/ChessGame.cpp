#include "../include/ChessGame.hpp"
#include <iostream>
#include <iomanip>
#include <algorithm>

ChessGame::ChessGame() {
    const int start[8][8] = {
        {-4,-2,-3,-5,-6,-3,-2,-4},
        {-1,-1,-1,-1,-1,-1,-1,-1},
        { 0, 0, 0, 0, 0, 0, 0, 0},
        { 0, 0, 0, 0, 0, 0, 0, 0},
        { 0, 0, 0, 0, 0, 0, 0, 0},
        { 0, 0, 0, 0, 0, 0, 0, 0},
        { 1, 1, 1, 1, 1, 1, 1, 1},
        { 4, 2, 3, 5, 6, 3, 2, 4}
    };

    std::memcpy(board, start, sizeof(board));
}

void ChessGame::executeCommand(std::unique_ptr<Command> cmd) {
    cmd->execute();
    history_.push(std::move(cmd));
    while (!redoStack_.empty()) redoStack_.pop();
}

void ChessGame::undoLastMove() {
    if (history_.empty()) {
        std::cout << "Nothing to undo!\n";
        return;
    }
    auto cmd = std::move(history_.top());
    history_.pop();
    cmd->undo();
    redoStack_.push(std::move(cmd));
}

void ChessGame::redoLastMove() {
    if (redoStack_.empty()) {
        std::cout << "Nothing to redo!\n";
        return;
    }
 
    auto cmd = std::move(redoStack_.top());
    redoStack_.pop();
    cmd->execute();
    history_.push(std::move(cmd));
}

void ChessGame::printBoard() const {
    std::cout << "  a b c d e f g h\n";
    for (int y = 0; y < 8; ++y) {
        std::cout << (8-y) << " ";
        for (int x = 0; x < 8; ++x) {
            char p = '.';
            int val = board[y][x];
            if (val != 0) {
                const char pieces[] = "PRNBQK";
                p = pieces[std::abs(val)-1];
                if (val < 0) p = tolower(p);
            }
 
            std::cout << p << ' ';
        }
 
        std::cout << (8-y) << "\n";
    }
 
    std::cout << "  a b c d e f g h\n\n";
}

void ChessGame::replayGame() const {
    std::cout << "Replaying all moves:\n";
    std::stack<std::unique_ptr<Command>> temp = history_;
    std::vector<std::string> moves;
    while (!temp.empty()) {
        moves.push_back(temp.top()->name());
        temp.pop();
    }
 
    std::reverse(moves.begin(), moves.end());
    for (size_t i = 0; i < moves.size(); ++i) {
        std::cout << (i/2 + 1) << (i%2==0 ? ". " : "... ") << moves[i] << "\n";
    }
}

// Helper functions used by commands
int ChessGame::getPieceAt(int x, int y) const { return board[y][x]; }
void ChessGame::setPieceAt(int x, int y, int piece) { board[y][x] = piece; }
char ChessGame::getPieceCharAt(int x, int y) const {
    int val = board[y][x];
    if (val == 0) return '.';
    const char* pieces = "PRNBQKprnbqk";
    return pieces[val > 0 ? val-1 : val+5];
}