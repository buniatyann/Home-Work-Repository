#ifndef VECTOR_HPP
#define VECTOR_HPP

#include "Point.hpp"
#include <cmath>
#include <stdexcept>
#include <iostream>
#include <algorithm>

template <std::size_t N, arithmetic_type T>
class Vector {
public:
    using value_type = T;
    using ld = long double;

    Vector();
    explicit Vector(const Point<N, T>& p);
    Vector(const Point<N, T>& a, const Point<N, T>& b);
    Vector(std::initializer_list<T> list);
    explicit Vector(const std::array<T, N>& arr);
    explicit Vector(const T& value); // fill all coordinates with the same scalar

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

    // template <std::size_t M, arithmetic_type U>
    // friend std::ostream& operator<<(std::ostream& os, const Vector<M, U>& v);

private:
    Point<N, T> data_;
};

#include "Vector.tpp"

#endif // VECTOR_HPP
