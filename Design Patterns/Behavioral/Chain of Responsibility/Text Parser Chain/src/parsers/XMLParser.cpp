#include "../../include/parsers/XMLParser.hpp"
#include <iostream>

ParseResult XMLParser::doParse(const std::string& input) {
    if (input.empty()) {
        return ParseResult::fail("Empty input");
    }
    if (input[0] == '<' && input.find('>') != std::string::npos) {
        std::cout << "[XMLParser] Detected XML tags → Parsing successful!\n";
        return ParseResult::ok("XML");
    }

    return ParseResult::fail("No XML tags found");
}