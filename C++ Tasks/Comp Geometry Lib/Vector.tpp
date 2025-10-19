#ifndef VECTOR_TPP
#define VECTOR_TPP

#include "Vector.hpp"
#include <cmath>
#include <algorithm>
#include <cassert>

// ============================================================================
// Constructors
// ============================================================================

template <typename T, std::size_t N>
Vector<T, N>::Vector() : data_{} {}

template <typename T, std::size_t N>
Vector<T, N>::Vector(const T& value) {
    data_.fill(Coord_t<T>(value));
}

template <typename T, std::size_t N>
Vector<T, N>::Vector(std::initializer_list<T> list) {
    if (list.size() != N) {
        throw std::invalid_argument("Vector: initializer list size must match dimension");
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

// ============================================================================
// Element Access
// ============================================================================

template <typename T, std::size_t N>
Coord_t<T>& Vector<T, N>::operator[](std::size_t pos) {
    assert(pos < N && "Vector index out of bounds");
    return data_[pos];
}

template <typename T, std::size_t N>
const Coord_t<T>& Vector<T, N>::operator[](std::size_t pos) const {
    assert(pos < N && "Vector index out of bounds");
    return data_[pos];
}

// ============================================================================
// Arithmetic Operators
// ============================================================================

template <typename T, std::size_t N>
Vector<T, N> Vector<T, N>::operator+(const Vector& rhs) const {
    Vector result;
    for (std::size_t i = 0; i < N; ++i) {
        result.data_[i] = data_[i] + rhs.data_[i];
    }

    return result;
}

template <typename T, std::size_t N>
Vector<T, N> Vector<T, N>::operator-(const Vector& rhs) const {
    Vector result;
    for (std::size_t i = 0; i < N; ++i) {
        result.data_[i] = data_[i] - rhs.data_[i];
    }
    
    return result;
}

template <typename T, std::size_t N>
Vector<T, N> Vector<T, N>::operator*(T scalar) const {
    Vector result;
    for (std::size_t i = 0; i < N; ++i) {
        result.data_[i] = data_[i] * scalar;
    }
    
    return result;
}

template <typename T, std::size_t N>
Vector<T, N> Vector<T, N>::operator/(T scalar) const {
    if (std::abs(scalar) < TOLERANCE) {
        throw std::domain_error("Vector division by zero");
    }

    Vector result;
    for (std::size_t i = 0; i < N; ++i) {
        result.data_[i] = data_[i] / scalar;
    }
    
    return result;
}

template <typename T, std::size_t N>
Vector<T, N>& Vector<T, N>::operator+=(const Vector& rhs) {
    for (std::size_t i = 0; i < N; ++i) {
        data_[i] += rhs.data_[i];
    }
    
    return *this;
}

template <typename T, std::size_t N>
Vector<T, N>& Vector<T, N>::operator-=(const Vector& rhs) {
    for (std::size_t i = 0; i < N; ++i) {
        data_[i] -= rhs.data_[i];
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
    if (std::abs(scalar) < TOLERANCE) {
        throw std::domain_error("Vector division by zero");
    }

    for (std::size_t i = 0; i < N; ++i) {
        data_[i] /= scalar;
    }
    
    return *this;
}

// ============================================================================
// Norms and Distances
// ============================================================================

template <typename T, std::size_t N>
typename Vector<T, N>::compute_type Vector<T, N>::norm1() const {
    compute_type sum = 0;
    for (const auto& coord : data_) {
        sum += std::abs(static_cast<compute_type>(coord));
    }
    
    return sum;
}

template <typename T, std::size_t N>
typename Vector<T, N>::compute_type Vector<T, N>::norm2() const {
    return std::sqrt(squared_norm());
}

template <typename T, std::size_t N>
typename Vector<T, N>::compute_type Vector<T, N>::length() const {
    return norm2();
}

template <typename T, std::size_t N>
typename Vector<T, N>::compute_type Vector<T, N>::squared_norm() const {
    compute_type sum = 0;
    for (const auto& coord : data_) {
        compute_type val = static_cast<compute_type>(coord);
        sum += val * val;
    }
    
    return sum;
}

template <typename T, std::size_t N>
typename Vector<T, N>::compute_type Vector<T, N>::distance(const Vector& rhs) const {
    return (*this - rhs).norm2();
}

// ============================================================================
// Vector Operations
// ============================================================================

template <typename T, std::size_t N>
typename Vector<T, N>::compute_type Vector<T, N>::dot(const Vector& rhs) const {
    compute_type result = 0;
    for (std::size_t i = 0; i < N; ++i) {
        result += static_cast<compute_type>(data_[i]) * static_cast<compute_type>(rhs.data_[i]);
    }
    
    return result;
}

template <typename T, std::size_t N>
bool Vector<T, N>::parallel(const Vector& rhs) const {
    if (squared_norm() < TOLERANCE * TOLERANCE || rhs.squared_norm() < TOLERANCE * TOLERANCE) {
        return false; // Zero vector is not parallel to anything
    }

    compute_type ratio = 0;
    bool ratio_set = false;
    for (std::size_t i = 0; i < N; ++i) {
        compute_type this_val = static_cast<compute_type>(data_[i]);
        compute_type rhs_val = static_cast<compute_type>(rhs.data_[i]);
        if (std::abs(this_val) < TOLERANCE && std::abs(rhs_val) < TOLERANCE) {
            continue;
        }
        // If one is zero and the other isn't, vectors are not parallel
        if (std::abs(this_val) < TOLERANCE || std::abs(rhs_val) < TOLERANCE) {
            return false;
        }
        
        compute_type current_ratio = this_val / rhs_val;
        if (!ratio_set) {
            ratio = current_ratio;
            ratio_set = true;
        } 
        else {
            // Check if ratios are consistent within tolerance
            compute_type ratio_diff = std::abs(current_ratio - ratio);
            compute_type relative_tolerance = TOLERANCE * std::max(std::abs(ratio), std::abs(current_ratio));    
            if (ratio_diff > relative_tolerance) {
                return false;
            }
        }
    }
    
    return ratio_set; // If no ratio was set, both vectors are effectively zero
}

template <typename T, std::size_t N>
Vector<T, N> Vector<T, N>::normalize() const {
    compute_type n = norm2();
    if (n < TOLERANCE) {
        throw std::domain_error("Cannot normalize zero-length vector");
    }

    return *this / static_cast<T>(n);
}

template <typename T, std::size_t N>
typename Vector<T, N>::compute_type Vector<T, N>::angle_between(const Vector& rhs) const {
    compute_type this_norm = norm2();
    compute_type rhs_norm = rhs.norm2();
    if (this_norm < TOLERANCE || rhs_norm < TOLERANCE) {
        throw std::domain_error("Cannot compute angle with zero-length vector");
    }

    compute_type cosine = dot(rhs) / (this_norm * rhs_norm);
    
    // Clamp to [-1, 1] to handle numerical errors
    cosine = std::max(static_cast<compute_type>(-1.0), 
                      std::min(static_cast<compute_type>(1.0), cosine));

    return std::acos(cosine);
}

template <typename T, std::size_t N>
Vector<T, N> Vector<T, N>::project_onto(const Vector& rhs) const {
    compute_type denom = rhs.squared_norm();
    if (denom < TOLERANCE * TOLERANCE) {
        throw std::domain_error("Cannot project onto zero vector");
    }

    compute_type scale = dot(rhs) / denom;
    return rhs * static_cast<T>(scale);
}

template <typename T, std::size_t N>
Vector<T, N> Vector<T, N>::reject_from(const Vector& rhs) const {
    return *this - project_onto(rhs);
}

template <typename T, std::size_t N>
Vector<T, N> Vector<T, N>::reflect_about(const Vector& normal) const {
    Vector n = normal.normalize();
    compute_type dot_product = dot(n);
    return *this - n * static_cast<T>(2 * dot_product);
}

// ============================================================================
// Dimension-Specific Operations (2D)
// ============================================================================

template <typename T, std::size_t N>
template<typename U>
std::enable_if_t<N == 2, Vector<T, N>> Vector<T, N>::perp() const {
    static_assert(N == 2, "perp() requires a 2D vector");
    return Vector({-data_[1], data_[0]});
}

template <typename T, std::size_t N>
template<typename U>
std::enable_if_t<N == 2, typename Vector<T, N>::compute_type> 
Vector<T, N>::cross(const Vector& rhs) const {
    static_assert(N == 2, "cross() for scalar result requires a 2D vector");
    return static_cast<compute_type>(data_[0]) * static_cast<compute_type>(rhs.data_[1]) - 
           static_cast<compute_type>(data_[1]) * static_cast<compute_type>(rhs.data_[0]);
}

// ============================================================================
// Dimension-Specific Operations (3D)
// ============================================================================

template <typename T, std::size_t N>
template<typename U>
std::enable_if_t<N == 3, Vector<T, N>> 
Vector<T, N>::vector_product(const Vector& rhs) const {
    static_assert(N == 3, "vector_product() requires a 3D vector");
    
    return Vector({
        data_[1] * rhs.data_[2] - data_[2] * rhs.data_[1],
        data_[2] * rhs.data_[0] - data_[0] * rhs.data_[2],
        data_[0] * rhs.data_[1] - data_[1] * rhs.data_[0]
    });
}

template <typename T, std::size_t N>
template<typename U>
std::enable_if_t<N == 3, typename Vector<T, N>::compute_type> 
Vector<T, N>::triple_scalar_product(const Vector& b, const Vector& c) const {
    static_assert(N == 3, "triple_scalar_product() requires 3D vectors");
    
    // Compute (a · (b × c)) more efficiently
    // This is equivalent to the determinant of the 3×3 matrix [a b c]
    return static_cast<compute_type>(data_[0]) * 
           (static_cast<compute_type>(b.data_[1]) * static_cast<compute_type>(c.data_[2]) - 
            static_cast<compute_type>(b.data_[2]) * static_cast<compute_type>(c.data_[1])) +
           static_cast<compute_type>(data_[1]) * 
           (static_cast<compute_type>(b.data_[2]) * static_cast<compute_type>(c.data_[0]) - 
            static_cast<compute_type>(b.data_[0]) * static_cast<compute_type>(c.data_[2])) +
           static_cast<compute_type>(data_[2]) * 
           (static_cast<compute_type>(b.data_[0]) * static_cast<compute_type>(c.data_[1]) - 
            static_cast<compute_type>(b.data_[1]) * static_cast<compute_type>(c.data_[0]));
}

#endif // VECTOR_TPP