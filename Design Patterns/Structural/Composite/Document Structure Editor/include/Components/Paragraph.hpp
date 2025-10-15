#ifndef PARAGRAPH_HPP
#define PARAGRAPH_HPP

#include "../Interface/IDocumentComponent.hpp"
#include <string>

class Paragraph : public IDocumentComponent {
public:
    Paragraph(const std::string& title, const std::string& content);
    std::size_t wordCount() const override;
    void applyFormat(const std::string& format) override;
    void display(const std::string& indent = "") const override;

private:
    std::string title_;
    std::string content_;
    std::size_t word_count_;
};

#endif // PARAGRAPH_HPP