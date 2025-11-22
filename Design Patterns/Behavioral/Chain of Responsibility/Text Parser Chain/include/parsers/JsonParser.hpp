#ifndef JSON_PARSER_HPP
#define JSON_PARSER_HPP

#include "../internal/Handler.hpp"

class JSONParser : public Handler {
protected:
    ParseResult doParse(const std::string& input) override;
};

#endif // JSON_PARSER_HPP