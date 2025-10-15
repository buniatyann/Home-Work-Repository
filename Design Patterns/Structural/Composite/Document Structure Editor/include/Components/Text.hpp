#ifndef TEXT_HPP
#define TEXT_HPP

#include "../Interface/IDocumentComponent.hpp"
#include <string>

class Text : public IDocumentComponent {
public:
    explicit Text(const std::string& content);
    std::size_t wordCount() const override;
    void applyFormat(const std::string& format) override;
    void display(const std::string& indent = "") const override;

private:
    std::string content_;
    std::size_t word_count_;
};

#endif // TEXT_HPP