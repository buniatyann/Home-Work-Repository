#ifndef RECT_HPP
#define RECT_HPP

#include <utility>
#include <cmath>

struct rect {
    double xmin;
    double ymin;
    double xmax;
    double ymax;

    rect();
    rect(double x1, double y1, double x2, double y2);

    double area() const;
    bool contains(const rect &r) const;
    bool intersects(const rect &r) const;
    static rect combine(const rect &a, const rect &b);
    double enlargement_needed(const rect &r) const;
    double min_dist_point(const std::pair<double,double>& p) const;
};

#endif // RECT_HPP