#ifndef POINT_TPP
#define POINT_TPP

#include "Point.hpp"

template <std::size_t N, arithmetic_type T>
Point<N, T>::Point() : arr_{} {}

template <std::size_t N, arithmetic_type T>
Point<N, T>::Point(std::initializer_list<T> list) {
    if (list.size() != N) throw std::invalid_argument("Point: wrong number of elements");
    std::copy(list.begin(), list.end(), arr_.begin());
}

template <std::size_t N, arithmetic_type T>
T& Point<N, T>::operator[](std::size_t pos) { return arr_[pos]; }

template <std::size_t N, arithmetic_type T>
const T& Point<N, T>::operator[](std::size_t pos) const { return arr_[pos]; }

template <std::size_t N, arithmetic_type T>
bool Point<N, T>::operator==(const Point& rhs) const { return arr_ == rhs.arr_; }

template <std::size_t N, arithmetic_type T>
bool Point<N, T>::operator!=(const Point& rhs) const { return arr_ != rhs.arr_; }

// template <std::size_t N, arithmetic_type T>
// std::ostream& operator<<(std::ostream& os, const Point<N, T>& p) {
//     os << "(";
//     for (std::size_t i = 0; i < N; ++i) {
//         os << p[i];
//         if (i + 1 < N) os << ", ";
//     }
//     os << ")";
//     return os;
// }


#endif // POINT_TPP