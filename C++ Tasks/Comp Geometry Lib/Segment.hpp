#ifndef SEGMENT_HPP
#define SEGMENT_HPP

#include "Point.hpp"

template <typename T, std::size_t N>
struct Segment {
    using point_t = Point<T, N>;

    point_t p1_;
    point_t p2_;

    Segment(const point_t& point1, const point_t& point2) : p1_(point1), p2_(point2) {}
    Segment(const Segment&) = default;
    Segment& operator=(const Segment&) = default;
    Segment(Segment&&) noexcept = default;
    Segment& operator=(Segment&&) noexcept = default;
};

// Returns true if the sequence of points A -> B -> C makes a counter-clockwise turn
template <typename T, std::size_t N>
bool isCounterClockwiseTurn(const Point<T, N>& A, const Point<T, N>& B, const Point<T, N>& C) {
    return Vector<T, N>(A, B).cross(Vector<T, N>(A, C)) > 0;
}

// Returns true if the two 2D segments intersect (excluding colinear overlaps or touching endpoints)
template <typename T, std::size_t N>
bool intersect(const Segment<T, N>& seg1, const Segment<T, N>& seg2) {
    // Let segment 1 be AB, and segment 2 be CD
    auto A = seg1.p1_;
    auto B = seg1.p2_;
    auto C = seg2.p1_;
    auto D = seg2.p2_;

    // Two segments AB and CD intersect if and only if:
    // - Points C and D are on different sides of segment AB
    // - Points A and B are on different sides of segment CD
    return (isCounterClockwiseTurn<T, N>(A, C, D) != isCounterClockwiseTurn<T, N>(B, C, D)) &&
        (isCounterClockwiseTurn<T, N>(A, B, C) != isCounterClockwiseTurn<T, N>(A, B, D));
}

#endif // SEGMENT_HPP

// class Ray; // Charagayt
// class Line; // ughigh
