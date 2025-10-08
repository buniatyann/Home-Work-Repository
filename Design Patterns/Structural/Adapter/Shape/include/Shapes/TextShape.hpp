#ifndef TEXTSHAPE_HPP
#define TEXTSHAPE_HPP

#include "../interface/IShape.hpp"
#include "../View/TextView.hpp"
#include <memory>
#include <iostream>

class TextShape : public IShape {
public:
    explicit TextShape(std::unique_ptr<TextView> textView);

    void boundingBox() const override;
    void setBoundingBox(Coordinate t1, Coordinate t2) override;
    std::unique_ptr<Manipulator> createManipulator() const override;
    void giveDescription() const override;

private:
    std::unique_ptr<TextView> textView_;
};

#endif // TEXTSHAPE_HPP
