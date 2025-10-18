#ifndef VECTOR_TPP
#define VECTOR_TPP

#include "Vector.hpp"
#include <cmath>
#include <algorithm>

template <typename T, std::size_t N>
Vector<T, N>::Vector() : data_{} {}

template <typename T, std::size_t N>
Vector<T, N>::Vector(const T& value) {
    data_.fill(Coord_t<T>(value));
}

template <typename T, std::size_t N>
Vector<T, N>::Vector(std::initializer_list<T> list) {
    if (list.size() != N) {
        throw std::invalid_argument("Vector: wrong number of elements");
    }

    std::size_t i = 0;
    for (const auto& val : list) {
        data_[i++] = Coord_t<T>(val);
    }
}

template <typename T, std::size_t N>
Vector<T, N>::Vector(const std::array<T, N>& arr) {
    for (std::size_t i = 0; i < N; ++i) {
        data_[i] = Coord_t<T>(arr[i]);
    }
}

template <typename T, std::size_t N>
Vector<T, N>::Vector(const Point<T, N>& p1, const Point<T, N>& p2) {
    *this = p2 - p1;
}

template <typename T, std::size_t N>
Coord_t<T>& Vector<T, N>::operator[](std::size_t pos) {
    return data_[pos];
}

template <typename T, std::size_t N>
const Coord_t<T>& Vector<T, N>::operator[](std::size_t pos) const {
    return data_[pos];
}

template <typename T, std::size_t N>
Vector<T, N> Vector<T, N>::operator+(const Vector& rhs) const {
    Vector result;
    for (std::size_t i = 0; i < N; ++i) {
        result[i] = data_[i] + rhs[i];
    }

    return result;
}

template <typename T, std::size_t N>
Vector<T, N> Vector<T, N>::operator-(const Vector& rhs) const {
    Vector result;
    for (std::size_t i = 0; i < N; ++i) {
        result[i] = data_[i] - rhs[i];
    }

    return result;
}

template <typename T, std::size_t N>
Vector<T, N> Vector<T, N>::operator*(T scalar) const {
    Vector result;
    for (std::size_t i = 0; i < N; ++i) {
        result[i] = data_[i] * scalar;
    }

    return result;
}

template <typename T, std::size_t N>
Vector<T, N> Vector<T, N>::operator/(T scalar) const {
    if (scalar == 0) {
        throw std::domain_error("Division by zero");
    }

    Vector result;
    for (std::size_t i = 0; i < N; ++i) {
        result[i] = data_[i] / scalar;
    }

    return result;
}

template <typename T, std::size_t N>
Vector<T, N>& Vector<T, N>::operator+=(const Vector& rhs) {
    for (std::size_t i = 0; i < N; ++i) {
        data_[i] += rhs[i];
    }

    return *this;
}

template <typename T, std::size_t N>
Vector<T, N>& Vector<T, N>::operator-=(const Vector& rhs) {
    for (std::size_t i = 0; i < N; ++i) {
        data_[i] -= rhs[i];
    }

    return *this;
}

template <typename T, std::size_t N>
Vector<T, N>& Vector<T, N>::operator*=(T scalar) {
    for (std::size_t i = 0; i < N; ++i) {
        data_[i] *= scalar;
    }

    return *this;
}

template <typename T, std::size_t N>
Vector<T, N>& Vector<T, N>::operator/=(T scalar) {
    if (scalar == 0) {
        throw std::domain_error("Division by zero");
    }

    for (std::size_t i = 0; i < N; ++i) {
        data_[i] /= scalar;
    }

    return *this;
}

template <typename T, std::size_t N>
typename Vector<T, N>::compute_type Vector<T, N>::norm1() const {
    compute_type sum = 0;
    for (const auto& coord : data_) {
        sum += std::abs(static_cast<T>(coord));
    }

    return sum;
}

template <typename T, std::size_t N>
typename Vector<T, N>::compute_type Vector<T, N>::norm2() const {
    compute_type sum = 0;
    for (const auto& coord : data_) {
        T val = coord;
        sum += val * val;
    }

    return std::sqrt(sum);
}

template <typename T, std::size_t N>
typename Vector<T, N>::compute_type Vector<T, N>::length() const {
    return norm2();
}

template <typename T, std::size_t N>
typename Vector<T, N>::compute_type Vector<T, N>::squared_norm() const {
    compute_type sum = 0;
    for (const auto& coord : data_) {
        auto val = coord;
        sum += val * val;
    }

    return sum;
}

template <typename T, std::size_t N>
typename Vector<T, N>::compute_type Vector<T, N>::distance(const Vector& rhs) const {
    return (*this - rhs).norm2();
}

template <typename T, std::size_t N>
typename Vector<T, N>::compute_type Vector<T, N>::dot(const Vector& rhs) const {
    compute_type result = 0;
    for (std::size_t i = 0; i < N; ++i) {
        result += data_[i] * rhs[i];
    }

    return result;
}

template <typename T, std::size_t N>
bool Vector<T, N>::parallel(const Vector& rhs) const {
    for (std::size_t i = 1; i < N; ++i) {
        if (data_[i - 1] * rhs[i] != data_[i] * rhs[i - 1]) {
            return false;
        }
    }

    return true;
}

template <typename T, std::size_t N>
Vector<T, N> Vector<T, N>::normalize() const {
    auto n = norm2();
    if (n == 0) {
        throw std::domain_error("normalize: zero-length vector");
    }

    return *this / static_cast<T>(n);
}

template <typename T, std::size_t N>
typename Vector<T, N>::compute_type Vector<T, N>::angle_between(const Vector& rhs) const {
    auto denom = norm2() * rhs.norm2();
    if (denom == 0) {
        throw std::domain_error("angle_between: zero-length vector");
    }

    auto cosine = dot(rhs) / denom;
    cosine = std::clamp(cosine, static_cast<compute_type>(-1), static_cast<compute_type>(1));

    return std::acos(cosine);
}

template <typename T, std::size_t N>
Vector<T, N> Vector<T, N>::project_onto(const Vector& rhs) const {
    auto denom = rhs.squared_norm();
    if (denom == 0) {
        throw std::domain_error("project_onto: zero vector");
    }

    return rhs * (dot(rhs) / denom);
}

template <typename T, std::size_t N>
Vector<T, N> Vector<T, N>::reject_from(const Vector& rhs) const {
    return *this - project_onto(rhs);
}

template <typename T, std::size_t N>
Vector<T, N> Vector<T, N>::reflect_about(const Vector& normal) const {
    Vector n = normal.normalize();
    return *this - n * (2 * dot(n));
}

// template <typename T, std::size_t N>
// Vector<T, N> Vector<T, N>::perp() const requires (N == 2) {
//     return Vector({-data_[1], data_[0]});
// }

template <typename T, std::size_t N>
Vector<T, N> Vector<T, N>::vector_product(const Vector& rhs) const requires (N == 3) {
    return Vector({
        data_[1] * rhs[2] - data_[2] * rhs[1],
        data_[2] * rhs[0] - data_[0] * rhs[2],
        data_[0] * rhs[1] - data_[1] * rhs[0]
    });
}

template <typename T, std::size_t N>
typename Vector<T, N>::compute_type Vector<T, N>::cross(const Vector& rhs) const requires (N == 2) {
    return data_[0] * rhs[1] - data_[1] * rhs[0];
}

template <typename T, std::size_t N>
typename Vector<T, N>::compute_type Vector<T, N>::triple_scalar_product(const Vector& b, const Vector& c) const requires (N == 3) {
    return this->dot(b.cross(c));
}

#endif // VECTOR_TPP
