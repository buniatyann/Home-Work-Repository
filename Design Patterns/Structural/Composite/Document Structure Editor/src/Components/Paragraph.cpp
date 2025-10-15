#include "../../include/Components/Paragraph.hpp"
#include <iostream>
#include <sstream>

Paragraph::Paragraph(const std::string& title, const std::string& content)
    : title_(title), content_(content) {
    std::istringstream iss(content);
    std::string word;
    word_count_ = 0;
    while (iss >> word) {
        ++word_count_;
    }
}

std::size_t Paragraph::wordCount() const {
    return word_count_;
}

void Paragraph::applyFormat(const std::string& format) {
    std::cout << "[" << format << "]" << title_ << ": " << content_ << "[/" << format << "]" << std::endl;
}

void Paragraph::display(const std::string& indent) const {
    std::cout << indent << "Paragraph: " << title_ << " (" << word_count_ << " words)" << std::endl;
    std::cout << indent << "  Content: " << content_ << std::endl;
}