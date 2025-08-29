#ifndef AABB_HPP
#define AABB_HPP

#include <vector>
#include <cassert>
#include <algorithm>

using point_t = std::vector<float>;

class AABB {
public:
    AABB(const point_t& min_point, const point_t& max_point, float margin = 0.0f);

    void extend(const AABB& other);
    bool overlaps(const AABB& other) const;
    float area() const;
    float distance_to_point(const point_t& p) const;

    const point_t& min() const;
    const point_t& max() const;

private:
    point_t min_;
    point_t max_;
    float margin_;
};

#endif // AABB_HPP
