#ifndef BOUNDINGBOX_HPP
#define BOUNDINGBOX_HPP

#include "Point.hpp"
#include "Coordinate.hpp"
#include <array>
#include <cstddef>

template <typename T, std::size_t N>
struct BoundingBox {
    using Point = Point<T, N>;

    std::array<coord_t<T>, N> min;
    std::array<coord_t<T>, N> max;
    bool valid;

    BoundingBox();
    explicit BoundingBox(const Point& p);

    void expand(const Point& p);
    void expand(const BoundingBox& other);

    bool contains(const Point& p) const;

    Point center() const;
    Point size() const;

    void clear();
};

#include "BoundingBox.tpp"

#endif // BOUNDING_BOX_HPP
