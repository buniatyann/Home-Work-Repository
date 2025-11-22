#include <iostream>
#include <memory>
#include <vector>
#include "include/parsers/JsonParser.hpp"
#include "include/parsers/XMLParser.hpp"
#include "include/parsers/CSVParser.hpp"
#include "include/parsers/PlainTextParser.hpp"

int main() {
    std::cout << "=== Chain of Responsibility: Universal Text Format Detector ===\n\n";
    auto chain = std::make_unique<JSONParser>();
    chain->setNext(std::make_unique<XMLParser>())
         ->setNext(std::make_unique<CSVParser>())
         ->setNext(std::make_unique<PlainTextParser>());

    std::vector<std::string> samples = {
        R"({"name": "Alice", "active": true})",
        R"(<user><name>Bob</name></user>)",
        "id,name,city\n1,Charlie,London",
        "This is just regular human text.",
        "gibberish123!@# no format"
    };

    for (const auto& text : samples) {
        std::cout << "INPUT:\n  " << text << "\n\n";
        ParseResult result = chain->handle(text);
        if (result.success) {
            std::cout << "SUCCESS → Final format: " << result.format << "\n";
        } 
        else {
            std::cout << "FAILED → " << result.error << "\n";
        }

        std::cout << std::string(60, '-') << "\n\n";
    }

    return 0;
}