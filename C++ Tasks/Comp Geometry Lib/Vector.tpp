#ifndef VECTOR_TPP
#define VECTOR_TPP

#include "Vector.hpp"

template <std::size_t N, arithmetic_type T>
Vector<N, T>::Vector() : data_{} {}

template <std::size_t N, arithmetic_type T>
Vector<N, T>::Vector(const Point<N, T>& p) : data_(p) {}

template <std::size_t N, arithmetic_type T>
Vector<N, T>::Vector(const Point<N, T>& a, const Point<N, T>& b) {
    for (std::size_t i = 0; i < N; ++i) {
        data_[i] = b[i] - a[i];
    }
}

template <std::size_t N, arithmetic_type T>
Vector<N, T>::Vector(std::initializer_list<T> list) {
    if (list.size() != N) {
        throw std::invalid_argument("Vector: wrong number of elements");
    }
    
    std::copy(list.begin(), list.end(), &data_[0]);
}

template <std::size_t N, arithmetic_type T>
Vector<N, T>::Vector(const std::array<T, N>& arr) {
    for (std::size_t i = 0; i < N; ++i) {
        data_[i] = arr[i];
    }
}

template <std::size_t N, arithmetic_type T>
Vector<N, T>::Vector(const T& value) {
    for (std::size_t i = 0; i < N; ++i) {
        data_[i] = value;
    }
}

template <std::size_t N, arithmetic_type T>
T& Vector<N, T>::operator[](std::size_t pos) { return data_[pos]; }

template <std::size_t N, arithmetic_type T>
const T& Vector<N, T>::operator[](std::size_t pos) const { return data_[pos]; }

template <std::size_t N, arithmetic_type T>
Vector<N, T> Vector<N, T>::operator+(const Vector& rhs) const {
    Vector result;
    for (std::size_t i = 0; i < N; ++i) {
        result[i] = data_[i] + rhs[i];
    }
    
    return result;
}

template <std::size_t N, arithmetic_type T>
Vector<N, T> Vector<N, T>::operator-(const Vector& rhs) const {
    Vector result;
    for (std::size_t i = 0; i < N; ++i) {
        result[i] = data_[i] - rhs[i];
    }
    
    return result;
}

template <std::size_t N, arithmetic_type T>
Vector<N, T> Vector<N, T>::operator*(T scalar) const {
    Vector result;
    for (std::size_t i = 0; i < N; ++i) {
        result[i] = data_[i] * scalar;
    }
    
    return result;
}

template <std::size_t N, arithmetic_type T>
Vector<N, T> Vector<N, T>::operator/(T scalar) const {
    if (scalar == 0) {
        throw std::domain_error("Division by zero");
    }
    
    Vector result;
    for (std::size_t i = 0; i < N; ++i) {
        result[i] = data_[i] / scalar;
    }
    
    return result;
}

template <std::size_t N, arithmetic_type T>
Vector<N, T>& Vector<N, T>::operator+=(const Vector& rhs) {
    for (std::size_t i = 0; i < N; ++i) {
        data_[i] += rhs[i];
    }
    
    return *this;
}

template <std::size_t N, arithmetic_type T>
Vector<N, T>& Vector<N, T>::operator-=(const Vector& rhs) {
    for (std::size_t i = 0; i < N; ++i) {
        data_[i] -= rhs[i];
    }
    
    return *this;
}

template <std::size_t N, arithmetic_type T>
Vector<N, T>& Vector<N, T>::operator*=(T scalar) {
    for (std::size_t i = 0; i < N; ++i) data_[i] *= scalar;
    return *this;
}

template <std::size_t N, arithmetic_type T>
Vector<N, T>& Vector<N, T>::operator/=(T scalar) {
    if (scalar == 0) {
        throw std::domain_error("Division by zero");
    }
    
    for (std::size_t i = 0; i < N; ++i) {
        data_[i] /= scalar;
    }
    
    return *this;
}

template <std::size_t N, arithmetic_type T>
typename Vector<N, T>::ld Vector<N, T>::norm1() const {
    ld ans = 0;
    for (std::size_t i = 0; i < N; ++i) {
        ans += std::abs(data_[i]);
    }
    
    return ans;
}

template <std::size_t N, arithmetic_type T>
typename Vector<N, T>::ld Vector<N, T>::norm2() const {
    ld ans = 0;
    for (std::size_t i = 0; i < N; ++i) {
        ans += static_cast<ld>(data_[i]) * data_[i];
    }
    
    return std::sqrt(ans);
}

template <std::size_t N, arithmetic_type T>
typename Vector<N, T>::ld Vector<N, T>::squared_norm() const {
    ld ans = 0;
    for (std::size_t i = 0; i < N; ++i) {
        ans += static_cast<ld>(data_[i]) * data_[i];
    }
    
    return ans;
}

template <std::size_t N, arithmetic_type T>
typename Vector<N, T>::ld Vector<N, T>::distance(const Vector& rhs) const {
    return (*this - rhs).norm2();
}

template <std::size_t N, arithmetic_type T>
typename Vector<N, T>::ld Vector<N, T>::dot(const Vector& rhs) const {
    ld ans = 0;
    for (std::size_t i = 0; i < N; ++i) {
        ans += static_cast<ld>(data_[i]) * rhs[i];
    }
    
    return ans;
}

template <std::size_t N, arithmetic_type T>
Vector<N, T> Vector<N, T>::normalize() const {
    ld n = norm2();
    if (n == 0) {
        throw std::domain_error("normalize: zero-length vector");
    }
    
    return *this / static_cast<T>(n);
}

template <std::size_t N, arithmetic_type T>
typename Vector<N, T>::ld Vector<N, T>::angle_between(const Vector& rhs) const {
    ld denom = norm2() * rhs.norm2();
    if (denom == 0) {
        throw std::domain_error("angle_between: zero-length vector");
    }
    
    ld cosine = dot(rhs) / denom;
    cosine = std::max(ld(-1), std::min(ld(1), cosine));
    return std::acos(cosine);
}

template <std::size_t N, arithmetic_type T>
Vector<N, T> Vector<N, T>::project_onto(const Vector& rhs) const {
    ld denom = rhs.squared_norm();
    if (denom == 0) {
        throw std::domain_error("project_onto: zero vector");
    }
    
    return rhs * (dot(rhs) / denom);
}

template <std::size_t N, arithmetic_type T>
Vector<N, T> Vector<N, T>::reject_from(const Vector& rhs) const {
    return *this - project_onto(rhs);
}

template <std::size_t N, arithmetic_type T>
Vector<N, T> Vector<N, T>::reflect_about(const Vector& normal) const {
    Vector n = normal.normalize();
    return *this - n * (2 * dot(n));
}

template <std::size_t N, arithmetic_type T>
Vector<N, T> Vector<N, T>::perp() const requires (N == 2) {
    return Vector(Point<N,T>{-data_[1], data_[0]});
}

template <std::size_t N, arithmetic_type T>
Vector<N, T> Vector<N, T>::cross(const Vector& rhs) const requires (N == 3) {
    return Vector(Point<3,T>{
        data_[1] * rhs[2] - data_[2] * rhs[1],
        data_[2] * rhs[0] - data_[0] * rhs[2],
        data_[0] * rhs[1] - data_[1] * rhs[0]
    });
}

template <std::size_t N, arithmetic_type T>
typename Vector<N, T>::ld Vector<N, T>::vector_product(const Vector& rhs) const requires (N == 2) {
    return static_cast<ld>(data_[0]) * rhs[1] - static_cast<ld>(data_[1]) * rhs[0];
}

template <std::size_t N, arithmetic_type T>
typename Vector<N, T>::ld Vector<N, T>::triple_scalar_product(const Vector& b, const Vector& c) const requires (N == 3) {
    return this->dot(b.cross(c));
}

// template <std::size_t N, arithmetic_type T>
// std::ostream& operator<<(std::ostream& os, const Vector<N, T>& v) {
//     os << "[";
//     for (std::size_t i = 0; i < N; ++i) {
//         os << v[i];
//         if (i + 1 < N) os << ", ";
//     }
//     os << "]";
//     return os;
// }


#endif // VECTOR_TPP