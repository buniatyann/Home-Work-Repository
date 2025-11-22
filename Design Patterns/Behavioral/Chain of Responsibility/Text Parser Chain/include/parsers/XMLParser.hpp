#ifndef XML_PARSER_HPP
#define XML_PARSER_HPP

#include "../internal/Handler.hpp"

class XMLParser : public Handler {
protected:
    ParseResult doParse(const std::string& input) override;
};

#endif // XML_PARSER_HPP