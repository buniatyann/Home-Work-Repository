#include "../../include/Composites/Section.hpp"
#include <iostream>
#include <algorithm>

Section::Section(const std::string& title) : title_(title) {}

void Section::add(std::shared_ptr<IDocumentComponent> component) {
    children_.push_back(component);
}

void Section::remove(std::shared_ptr<IDocumentComponent> component) {
    children_.erase(
        std::remove(children_.begin(), children_.end(), component),
        children_.end()
    );
}

std::size_t Section::wordCount() const {
    std::size_t total = 0;
    for (const auto& child : children_) {
        total += child->wordCount();
    }
 
    return total;
}

void Section::applyFormat(const std::string& format) {
    std::cout << "[" << format << "]" << title_ << ": ";
    for (const auto& child : children_) {
        child->applyFormat(format);
    }
 
    std::cout << "[/" << format << "]" << std::endl;
}

void Section::display(const std::string& indent) const {
    std::cout << indent << "Section: " << title_ << std::endl;
    for (const auto& child : children_) {
        child->display(indent + "  ");
    }
}