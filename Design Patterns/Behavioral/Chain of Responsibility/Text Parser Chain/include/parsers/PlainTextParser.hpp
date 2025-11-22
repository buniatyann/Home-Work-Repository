#ifndef PLAIN_TEXT_PARSER_HPP
#define PLAIN_TEXT_PARSER_HPP

#include "../internal/Handler.hpp"

class PlainTextParser : public Handler {
protected:
    ParseResult doParse(const std::string& input) override;
};

#endif // PLAIN_TEXT_PARSER_HPP