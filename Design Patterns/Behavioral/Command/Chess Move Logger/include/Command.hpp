#ifndef COMMAND_HPP
#define COMMAND_HPP

#include <string>

class ChessGame;

class Command {
public:
    virtual ~Command() = default;
    virtual void execute() = 0;
    virtual void undo() = 0;
    virtual std::string name() const = 0;
};

#endif // COMMAND_HPP