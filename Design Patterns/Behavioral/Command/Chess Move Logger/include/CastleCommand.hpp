#ifndef CASTLE_COMMAND_HPP
#define CASTLE_COMMAND_HPP

#include "Command.hpp"

class CastleCommand : public Command {
public:
    enum Type { KINGSIDE, QUEENSIDE };
    CastleCommand(ChessGame* game, Type type);
    void execute() override;
    void undo() override;
    std::string name() const override;

private:
    ChessGame* game_;
    Type type_;
};

#endif // CASTLE_COMMAND_HPP