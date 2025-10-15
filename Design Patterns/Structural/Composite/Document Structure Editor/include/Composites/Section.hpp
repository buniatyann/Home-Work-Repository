#ifndef SECTION_HPP
#define SECTION_HPP

#include "../Interface/IDocumentComponent.hpp"
#include <memory>
#include <string>
#include <vector>

class Section : public IDocumentComponent {
public:
    explicit Section(const std::string& title);
    void add(std::shared_ptr<IDocumentComponent> component);
    void remove(std::shared_ptr<IDocumentComponent> component);
    std::size_t wordCount() const override;
    void applyFormat(const std::string& format) override;
    void display(const std::string& indent = "") const override;

private:
    std::string title_;
    std::vector<std::shared_ptr<IDocumentComponent>> children_;
};

#endif // SECTION_HPP