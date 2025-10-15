#include "include/Composites/Document.hpp"
#include "include/Composites/Section.hpp"
#include "include/Components/Text.hpp"
#include "include/Components/Paragraph.hpp"
#include <memory>

int main() {
    auto doc = std::make_shared<Document>("My Book");
    auto chapter1 = std::make_shared<Section>("Chapter 1");
    auto text1 = std::make_shared<Text>("This is a simple text element.");
    auto para1 = std::make_shared<Paragraph>("Introduction", "This is the first paragraph of the chapter.");
    chapter1->add(text1);
    chapter1->add(para1);
    auto subsection = std::make_shared<Section>("Subsection 1.1");
    auto para2 = std::make_shared<Paragraph>("Details", "This is a paragraph in the subsection.");
    subsection->add(para2);
    chapter1->add(subsection);
    doc->add(chapter1);
    std::cout << "Document Structure:\n";
    doc->display();
    std::cout << "\nTotal words in document: " << doc->wordCount() << "\n";
    std::cout << "\nFormatted Document (Bold):\n";
    doc->applyFormat("bold");

    return 0;
}