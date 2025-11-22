#include "../../include/parsers/CSVParser.hpp"
#include <iostream>

ParseResult CSVParser::doParse(const std::string& input) {
    if (input.find(',') != std::string::npos) {
        std::cout << "[CSVParser] Found commas → Treating as CSV → Parsing successful!\n";
        return ParseResult::ok("CSV");
    }

    return ParseResult::fail("No commas found");
}