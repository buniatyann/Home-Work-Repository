#ifndef PROMOTE_COMMAND_HPP
#define PROMOTE_COMMAND_HPP

#include "Command.hpp"

class PromoteCommand : public Command {
public:
    PromoteCommand(ChessGame* game, int x, int y, char newPiece); // 'Q', 'R', 'B', 'N'
    void execute() override;
    void undo() override;
    std::string name() const override;

private:
    ChessGame* game_;
    int x_, y_;
    char newPiece_;
    char oldPiece_; // always 'P'
};

#endif // PROMOTE_COMMAND_HPP