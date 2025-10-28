#ifndef POLYGON_HPP
#define POLYGON_HPP

#include "Point.hpp"
#include "Segment.hpp"
#include "BoundingBox.hpp"

#include <vector>
#include <cstddef>
#include <type_traits>
#include <cassert>

template <typename T, std::size_t N>
class Polygon {
public:
    static_assert(N > 0, "N must be greater than 0");
    static_assert(std::is_arithmetic<T>::value, "T must be arithmetic type");

    using Point = Point<T, N>;
    using coord_t = coord_t<T>;
    using Segment = Segment<T, N>;

public:
    Polygon();
    Polygon(const Polygon& other);
    Polygon& operator=(const Polygon& other);
    Polygon(Polygon&& other) noexcept;
    Polygon& operator=(Polygon&& other) noexcept;
    ~Polygon();

    BoundingBox<T, N> boundingBox() const;

    Point& operator[](std::size_t ind);
    const Point& operator[](std::size_t ind) const;

    bool empty() const;
    std::size_t size() const;

    bool isConvex() const;
    bool contains(const Point& p) const;
    auto area() const;
    auto perimeter() const;
    bool isClockwise() const;
    void makeCounterClockwise();
    bool isSimple() const;

    std::vector<Segment> edges() const;
    std::vector<Point> vertices() const;

    void push_back(const Point& p);
    void insert(const Point& p, std::size_t index);

private:
    std::vector<Point> data_;
    mutable BoundingBox<T> box_;
    mutable bool boxDirty_ = true;
};

#include "Polygon.tpp"

#endif // POLYGON_HPP