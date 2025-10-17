#ifndef RAY_HPP
#define RAY_HPP

#include "Point.hpp"

template <typename T, std::size_t N>
struct Ray {
    using point_t = Point<T, N>;
    
    Ray(const point_t& point1, const point_t& point2) : p1_(point1), p2_(point2) {}
    Ray(const Ray&) = default;
    Ray& operator=(const Ray&) = default;
    Ray(Ray&&) noexcept = default;
    Ray& operator=(Ray&&) noexcept = default;

    point_t p1_; // start point
    point_t p2_; // point defining direction
};

template <typename T, std::size_t N>
bool intersect(const Ray<T, N>& ray1, const Ray<T, N>& ray2) {
    static_assert(N == 2, "Ray-ray intersection is only implemented for 2D.");

    auto epsilon = Vector<T, N>::TOLERANCE;

    auto P0 = ray1.p1_;
    auto P1 = ray1.p2_;
    auto Q0 = ray2.p1_;
    auto Q1 = ray2.p2_;

    Vector<T, N> r = P1 - P0; // direction of ray1
    Vector<T, N> s = Q1 - Q0; // direction of ray2
    Vector<T, N> w = Q0 - P0; // vector from P0 to Q0

    auto r_cross_s = r.cross(s);  // scalar in 2D
    auto w_cross_r = w.cross(r);

    if (std::abs(r_cross_s) < epsilon) {
        if (std::abs(w_cross_r) < epsilon) {
            auto t0 = w.dot(r) / r.dot(r);
            return t0 >= 0;
        } 
        else {
            return false; // parallel but not collinear
        }
    } 
    else {
        auto t = w.cross(s) / r_cross_s;
        auto u = w.cross(r) / r_cross_s;
        return t >= 0 && u >= 0;
    }
}

#endif // RAY_HPP
