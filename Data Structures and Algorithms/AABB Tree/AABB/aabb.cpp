#include "aabb.hpp"
#include <cmath>

AABB::AABB(const point_t& min_point, const point_t& max_point, float margin)
    : min_(min_point), max_(max_point), margin_(margin) {
    assert(min_.size() == max_.size());
    for (size_t i = 0; i < min_.size(); ++i) {
        min_[i] -= margin_;
        max_[i] += margin_;
    }
}

void AABB::extend(const AABB& other) {
    assert(other.min_.size() == min_.size());
    for (size_t i = 0; i < min_.size(); ++i) {
        min_[i] = std::min(min_[i], other.min_[i]);
        max_[i] = std::max(max_[i], other.max_[i]);
    }
}

bool AABB::overlaps(const AABB& other) const {
    assert(other.min_.size() == min_.size());
    for (size_t i = 0; i < min_.size(); ++i) {
        if (max_[i] < other.min_[i] || min_[i] > other.max_[i]){
            return false;
        }
    }
    
    return true;
}

float AABB::area() const {
    float a = 1.0f;
    for (size_t i = 0; i < min_.size(); ++i) {
        a *= (max_[i] - min_[i]);
    }
    
    return a;
}

float AABB::distance_to_point(const point_t& p) const {
    assert(p.size() == min_.size());
    float sum_sq = 0.0f;
    for (size_t i = 0; i < p.size(); ++i) {
        float v = 0.0f;
        if (p[i] < min_[i]) {
            v = min_[i] - p[i];
        }
        else if (p[i] > max_[i]) {
            v = p[i] - max_[i];
        }
        
        sum_sq += v * v;
    }
 
    return std::sqrt(sum_sq);
}

const point_t& AABB::min() const { return min_; }
const point_t& AABB::max() const { return max_; }
