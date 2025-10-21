#ifndef LINE_HPP
#define LINE_HPP

#include "Point.hpp"

template <typename T, std::size_t N>
struct Line {
    using point_t = Point<T, N>;

    point_t p1_;
    point_t p2_;

    Line(const point_t& point1, const point_t& point2) : p1_(point1), p2_(point2) {}
    Line(const Line&) = default;
    Line& operator=(const Line&) = default;
    Line(Line&&) noexcept = default;
    Line& operator=(Line&&) noexcept = default;
};


template <typename T, std::size_t N>
bool intersect(const Line<T, N>& line1, const Line<T, N>& line2) {
    using Vector = Vector<T,N>;

    Vector directional1(line1.p2_, line1.p1_);
    Vector directional2(line2.p2_, line2.p1_);

    return directional1.parallel(directional2);
}

#endif // LINE_HPP
