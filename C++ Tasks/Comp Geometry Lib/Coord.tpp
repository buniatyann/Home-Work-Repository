#ifndef COORD_TPP
#define COORD_TPP

#include <cmath>
#include <type_traits>
#include "Coord.hpp"

template <typename T>
Coord_t<T>::Coord_t() = default;

template <typename T>
Coord_t<T>::Coord_t(const T& other) : coord(other) {}

template <typename T>
bool Coord_t<T>::operator==(const Coord_t<T>& other) const {
    if constexpr (std::is_floating_point_v<T>) {
        return std::abs(coord - other.coord) <= tolerance;
    } 
    else {
        return coord == other.coord;
    }
}

template <typename T>
bool Coord_t<T>::operator!=(const Coord_t<T>& other) const {
    return !(*this == other);
}

template <typename T>
Coord_t<T> Coord_t<T>::operator+(const Coord_t<T>& other) const {
    return Coord_t(coord + other.coord);
}

template <typename T>
Coord_t<T> Coord_t<T>::operator-(const Coord_t<T>& other) const {
    return Coord_t(coord - other.coord);
}

template <typename T>
Coord_t<T> Coord_t<T>::operator*(const T& scalar) const {
    return Coord_t(coord * scalar);
}

template <typename T>
Coord_t<T> Coord_t<T>::operator/(const T& scalar) const {
    return Coord_t(coord / scalar);
}

template <typename T>
Coord_t<T>::operator T&() {
    return coord;
}

template <typename T>
Coord_t<T>::operator const T&() const {
    return coord;
}

template <typename T>
Coord_t<T>::operator double() const {
    return static_cast<double>(coord);
}

#endif // COORD_TPP
