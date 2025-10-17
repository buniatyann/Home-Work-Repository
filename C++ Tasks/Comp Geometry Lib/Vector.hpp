#ifndef VECTOR_HPP
#define VECTOR_HPP

#include "Coord.hpp"
#include <cmath>
#include <cstddef>
#include <stdexcept>
#include <iostream>
#include <algorithm>
#include <initializer_list>
#include <array>
#include <iterator>

template <typename T, std::size_t N>
class Vector;

template <typename T, std::size_t N>
using Point = Vector<T, N>;


template <typename T, std::size_t N>
class Vector {
public:
    static constexpr TOLERANCE = 1e-9;

    using value_type = T;
    using reference = T&;
    using const_reference = const T&;
    using pointer = T*;
    using const_pointer = const T*;
    using iterator = typename std::array<Coord_t<T>, N>::iterator;
    using const_iterator = typename std::array<Coord_t<T>, N>::const_iterator;
    using ld = long double;

    Vector();
    explicit Vector(const T& value); // fill all coordinates with the same scalar
    Vector(std::initializer_list<T> list);
    explicit Vector(const std::array<T, N>& arr);
    Vector(const Point<T, N>& p1, const Point<T, N>& p2) {
        p1.operator-(p2);
    }

    Vector(const Vector& rhs) = default;
    Vector(Vector&& rhs) noexcept = default;
    Vector& operator=(const Vector& rhs) = default;
    Vector& operator=(Vector&& rhs) noexcept = default;

    T& operator[](std::size_t pos);
    const T& operator[](std::size_t pos) const;

    Vector operator+(const Vector& rhs) const;
    Vector operator-(const Vector& rhs) const;
    Vector operator*(T scalar) const;
    Vector operator/(T scalar) const;

    Vector& operator+=(const Vector& rhs);
    Vector& operator-=(const Vector& rhs);
    Vector& operator*=(T scalar);
    Vector& operator/=(T scalar);

    ld norm1() const;
    ld norm2() const;
    ld length() const; // internally calls norm 2
    ld squared_norm() const;
    ld distance(const Vector& rhs) const;
    ld dot(const Vector& rhs) const;

    Vector normalize() const;
    ld angle_between(const Vector& rhs) const;
    Vector project_onto(const Vector& rhs) const;
    Vector reject_from(const Vector& rhs) const;
    Vector reflect_about(const Vector& normal) const;

    Vector perp() const requires (N == 2);
    Vector cross(const Vector& rhs) const requires (N == 3);
    ld vector_product(const Vector& rhs) const requires (N == 2);
    ld triple_scalar_product(const Vector& b, const Vector& c) const requires (N == 3);

    // Iterators
    iterator begin() { return data_.begin(); }
    iterator end() { return data_.end(); }

    const_iterator begin() const { return data_.begin(); }
    const_iterator end() const { return data_.end(); }

    const_iterator cbegin() const { return data_.cbegin(); }
    const_iterator cend() const { return data_.cend(); }

private:
    std::array<Coord_t<T>, N> data_;
};

#include "Vector.tpp"

#endif // VECTOR_HPP
