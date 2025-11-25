#ifndef MOVE_COMMAND_HPP
#define MOVE_COMMAND_HPP

#include "Command.hpp"
#include <string>

class MoveCommand : public Command {
public:
    MoveCommand(ChessGame* game, int fromX, int fromY, int toX, int toY);
    void execute() override;
    void undo() override;
    std::string name() const override { return notation_; }

private:
    ChessGame* game_;
    int fromX_, fromY_, toX_, toY_;
    std::string notation_;
    int capturedPiece_;  // = -1 if none
};

#endif // MOVE_COMMAND_HPP