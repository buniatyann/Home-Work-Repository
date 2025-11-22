#ifndef CSV_PARSER_HPP
#define CSV_PARSER_HPP

#include "../internal/Handler.hpp"

class CSVParser : public Handler {
protected:
    ParseResult doParse(const std::string& input) override;
};

#endif // CSV_PARSER_HPP