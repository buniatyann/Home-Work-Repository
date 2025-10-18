#ifndef VECTOR_HPP
#define VECTOR_HPP

#include "Coord.hpp"
#include <array>
#include <cmath>
#include <cstddef>
#include <initializer_list>
#include <stdexcept>
#include <algorithm>

template <typename T, std::size_t N>
class Vector;

template <typename T, std::size_t N>
using Point = Vector<T, N>;

template <typename T, std::size_t N>
class Vector {
public:
    static constexpr double TOLERANCE = 1e-9;

    using value_type = T;
    using reference = Coord_t<T>&;
    using const_reference = const Coord_t<T>&;
    using pointer = Coord_t<T>*;
    using const_pointer = const Coord_t<T>*;
    using iterator = typename std::array<Coord_t<T>, N>::iterator;
    using const_iterator = typename std::array<Coord_t<T>, N>::const_iterator;
    using compute_type = long double;

    Vector();
    explicit Vector(const T& value);
    Vector(std::initializer_list<T> list);
    explicit Vector(const std::array<T, N>& arr);
    Vector(const Point<T, N>& p1, const Point<T, N>& p2);

    Vector(const Vector& rhs) = default;
    Vector(Vector&& rhs) noexcept = default;
    Vector& operator=(const Vector& rhs) = default;
    Vector& operator=(Vector&& rhs) noexcept = default;

    Coord_t<T>& operator[](std::size_t pos);
    const Coord_t<T>& operator[](std::size_t pos) const;

    Vector operator+(const Vector& rhs) const;
    Vector operator-(const Vector& rhs) const;
    Vector operator*(T scalar) const;
    Vector operator/(T scalar) const;

    Vector& operator+=(const Vector& rhs);
    Vector& operator-=(const Vector& rhs);
    Vector& operator*=(T scalar);
    Vector& operator/=(T scalar);

    compute_type norm1() const;
    compute_type norm2() const;
    compute_type length() const;
    compute_type squared_norm() const;
    compute_type distance(const Vector& rhs) const;
    compute_type dot(const Vector& rhs) const;
    bool parallel(const Vector& rhs) const;

    Vector normalize() const;
    compute_type angle_between(const Vector& rhs) const;
    Vector project_onto(const Vector& rhs) const;
    Vector reject_from(const Vector& rhs) const;
    Vector reflect_about(const Vector& normal) const;

    // Vector perp() const requires (N == 2);
    Vector vector_product(const Vector& rhs) const requires (N == 3);
    compute_type cross(const Vector& rhs) const requires (N == 2);
    compute_type triple_scalar_product(const Vector& b, const Vector& c) const requires (N == 3);

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
