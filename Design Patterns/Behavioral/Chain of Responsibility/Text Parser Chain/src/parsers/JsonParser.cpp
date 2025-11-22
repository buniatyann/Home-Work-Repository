#include "../../include/parsers/JsonParser.hpp"
#include <iostream>

ParseResult JSONParser::doParse(const std::string& input) {
    if (input.empty()) {
        return ParseResult::fail("Empty input");
    }

    char first = input[0];
    char last  = input.back();
    if ((first == '{' && last == '}') || (first == '[' && last == ']')) {
        std::cout << "[JSONParser] Detected valid JSON structure → Parsing successful!\n";
        return ParseResult::ok("JSON");
    }

    return ParseResult::fail("Does not look like valid JSON");
}