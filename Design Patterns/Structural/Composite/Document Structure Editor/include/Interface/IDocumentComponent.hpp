#ifndef IDOCUMENT_COMPONENT_HPP
#define IDOCUMENT_COMPONENT_HPP

#include <memory>
#include <string>
#include <cstddef>

class IDocumentComponent {
public:
    virtual ~IDocumentComponent() = default;
    virtual std::size_t wordCount() const = 0;
    virtual void applyFormat(const std::string& format) = 0;
    virtual void display(const std::string& indent = "") const = 0;
};

#endif // IDOCUMENT_COMPONENT_HPP