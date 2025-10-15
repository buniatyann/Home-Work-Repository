#include "../../include/Composites/Document.hpp"
#include <iostream>
#include <algorithm>

Document::Document(const std::string& title) : title_(title) {}

void Document::add(std::shared_ptr<IDocumentComponent> component) {
    components_.push_back(component);
}

void Document::remove(std::shared_ptr<IDocumentComponent> component) {
    components_.erase(
        std::remove(components_.begin(), components_.end(), component),
        components_.end()
    );
}

std::size_t Document::wordCount() const {
    std::size_t total = 0;
    for (const auto& component : components_) {
        total += component->wordCount();
    }
 
    return total;
}

void Document::applyFormat(const std::string& format) {
    std::cout << "[" << format << "]Document: " << title_ << std::endl;
    for (const auto& component : components_) {
        component->applyFormat(format);
    }
 
    std::cout << "[/" << format << "]" << std::endl;
}

void Document::display(const std::string& indent) const {
    std::cout << indent << "Document: " << title_ << std::endl;
    for (const auto& component : components_) {
        component->display(indent + "  ");
    }
}