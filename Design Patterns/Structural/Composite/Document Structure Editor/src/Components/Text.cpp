#include "../../include/Components/Text.hpp"
#include <iostream>
#include <sstream>

Text::Text(const std::string& content) : content_(content) {
    std::istringstream iss(content);
    std::string word;
    word_count_ = 0;
    while (iss >> word) {
        ++word_count_;
    }
}

std::size_t Text::wordCount() const {
    return word_count_;
}

void Text::applyFormat(const std::string& format) {
    std::cout << "[" << format << "]" << content_ << "[/" << format << "]" << std::endl;
}

void Text::display(const std::string& indent) const {
    std::cout << indent << "Text: " << content_ << " (" << word_count_ << " words)" << std::endl;
}