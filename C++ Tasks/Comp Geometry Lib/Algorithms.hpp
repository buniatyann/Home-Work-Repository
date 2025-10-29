#ifndef ALGORITHMS_HPP
#define ALGORITHMS_HPP

#include "Point.hpp"
#include "Segment.hpp"
#include "Line.hpp"
#include "Ray.hpp"
#include "BoundingBox.hpp"
#include "Polygon.hpp"
#include <set>

namespace algo {

template <typename T, std::size_t N>
bool intersect(const Segment<T,N>& seg1, const Segment<T,N>& seg2);

template <typename T, std::size_t N>
bool intersect(const Ray<T,N>& ray1, const Ray<T,N>& ray2);

template <typename T, std::size_t N>
bool intersect(const Line<T,N>& line1, const Line<T,N>& line2);

template <typename T, std::size_t N>
bool intersect(const Line<T,N>& AB, const Segment<T,N>& CD);

template <typename T, std::size_t N>
bool intersect(const Segment<T,N>& CD, const Line<T,N>& AB);

template <typename T, std::size_t N>
bool intersect(const Ray<T,N>& AB, const Line<T,N>& CD);

template <typename T, std::size_t N>
bool intersect(const Line<T,N>& CD, const Ray<T,N>& AB);

template <typename T, std::size_t N>
bool intersect(const Segment<T,N>& AB, const Ray<T,N>& CD);

template <typename T, std::size_t N>
bool intersect(const Ray<T,N>& CD, const Segment<T,N>& AB);

template <typename T, std::size_t N>
constexpr bool intersect(const BoundingBox<T,N>& a, const BoundingBox<T,N>& b);

template <typename T, std::size_t N>
bool intersect(const Polygon<T,N>& P1, const Polygon<T,N>& P2) noexcept;

} // namespace algo

#include "Algorithms.tpp"

#endif // ALGORITHMS_HPP