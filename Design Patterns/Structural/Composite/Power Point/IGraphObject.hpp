#ifndef IGRAPH_OBJECT_HPP
#define IGRAPH_OBJECT_HPP

#include <memory>
#include <iostream>

class IGraphObject {
public:
    virtual ~IGraphObject() = default;
    virtual void draw() const = 0;
};

#endif // IGRAPH_OBJECT_HPP