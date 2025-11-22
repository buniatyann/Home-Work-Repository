#include "../../include/parsers/PlainTextParser.hpp"
#include <iostream>

ParseResult PlainTextParser::doParse(const std::string& input) {
    std::cout << "[PlainTextParser] No known format detected → Falling back to plain text → Accepted!\n";
    return ParseResult::ok("PlainText");
}