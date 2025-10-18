#ifndef COORD_HPP
#define COORD_HPP

#include <cmath>
#include <type_traits>

template <typename T>
struct Coord_t
{
    static_assert(std::is_arithmetic_v<T>, "type is not arithmetic");

    Coord_t();
    Coord_t(const T& other);

    bool operator==(const Coord_t& other) const;
    bool operator!=(const Coord_t& other) const;

    Coord_t operator+(const Coord_t& other) const;
    Coord_t operator-(const Coord_t& other) const;
    Coord_t operator*(const T& scalar) const;
    Coord_t operator/(const T& scalar) const;

    operator T&();
    operator const T&() const;
	operator double() const;

    T coord;

    static constexpr long double tolerance = std::is_floating_point_v<T> ? 0.0001 : 0;
};

#include "Coord.tpp"  

#endif // COORD_HPP
