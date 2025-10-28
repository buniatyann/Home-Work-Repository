#ifndef BOUNDINGBOX_TPP
#define BOUNDINGBOX_TPP

#include "BoundingBox.hpp"
#include <limits>
#include <cassert>
#include <algorithm>

template <typename T, std::size_t N>
BoundingBox<T, N>::BoundingBox()
    : valid(false)
{
    for (std::size_t i = 0; i < N; ++i) {
        min[i] = std::numeric_limits<T>::max();
        max[i] = std::numeric_limits<T>::lowest();
    }
}

template <typename T, std::size_t N>
BoundingBox<T, N>::BoundingBox(const Point& p)
    : BoundingBox()
{
    expand(p);
}

template <typename T, std::size_t N>
void BoundingBox<T, N>::expand(const Point& p) {
    if (!valid) {
        min = p.data;
        max = p.data;
        valid = true;
    } 
    else {
        for (std::size_t i = 0; i < N; ++i) {
            if (p[i] < min[i]) { 
                min[i] = p[i];
            }
            if (p[i] > max[i]) {
                max[i] = p[i];
            }
        }
    }
}

template <typename T, std::size_t N>
void BoundingBox<T, N>::expand(const BoundingBox& other) {
    if (!other.valid) {
        return;
    }
    
    if (!valid) {
        *this = other;
    } 
    else {
        for (std::size_t i = 0; i < N; ++i) {
            if (other.min[i] < min[i]) {
                min[i] = other.min[i];
            }
            if (other.max[i] > max[i]) {
                max[i] = other.max[i];
            }
        }
    }
}

template <typename T, std::size_t N>
bool BoundingBox<T, N>::contains(const Point& p) const {
    if (!valid) {
        return false;
    }
    
    for (std::size_t i = 0; i < N; ++i) {
        if (p[i] < min[i] || p[i] > max[i]) {
            return false;
        }
    }
    
    return true;
}

template <typename T, std::size_t N>
typename BoundingBox<T, N>::Point BoundingBox<T, N>::center() const {
    assert(valid);
    Point c;
    for (std::size_t i = 0; i < N; ++i) {
        c[i] = (min[i] + max[i]) / T(2);
    }

    return c;
}

template <typename T, std::size_t N>
typename BoundingBox<T, N>::Point BoundingBox<T, N>::size() const {
    assert(valid);
    Point s;
    for (std::size_t i = 0; i < N; ++i) {
        s[i] = max[i] - min[i];
    }
   
    return s;
}

template <typename T, std::size_t N>
void BoundingBox<T, N>::clear() {
    for (std::size_t i = 0; i < N; ++i) {
        min[i] = std::numeric_limits<T>::max();
        max[i] = std::numeric_limits<T>::lowest();
    }
   
    valid = false;
}

#endif // BOUNDING_BOX_TPP