#ifndef POINT_HPP
#define POINT_HPP

#include <array>
#include <initializer_list>
#include <iostream>
#include <stdexcept>
#include <type_traits>

template <typename T>
concept arithmetic_type = std::is_arithmetic_v<T>;

template <std::size_t N, arithmetic_type T>
class Point {
public:
    using value_type = T;
    using container_type = std::array<T, N>;
    using size_type = std::size_t;

    Point();
    Point(std::initializer_list<T> list);
    Point(const Point&) = default;
    Point(Point&&) noexcept = default;
    Point& operator=(const Point&) = default;
    Point& operator=(Point&&) noexcept = default;

    T& operator[](std::size_t pos);
    const T& operator[](std::size_t pos) const;

    bool operator==(const Point& rhs) const;
    bool operator!=(const Point& rhs) const;

    // template <std::size_t M, arithmetic_type U>
    // friend std::ostream& operator<<(std::ostream& os, const Point<M, U>& p);

private:
    container_type arr_;
};

#include "Point.tpp"

#endif // POINT_HPP
