#include "rect.hpp"

rect::rect() : xmin(0), ymin(0), xmax(0), ymax(0) {}
rect::rect(double x1, double y1, double x2, double y2)
    : xmin(std::min(x1, x2)),
      ymin(std::min(y1, y2)),
      xmax(std::max(x1, x2)),
      ymax(std::max(y1, y2)) {}

double rect::area() const {
    double w = std::max(0.0, xmax - xmin);
    double h = std::max(0.0, ymax - ymin);
    
    return w * h;
}

bool rect::contains(const rect &r) const {
    return xmin <= r.xmin && ymin <= r.ymin && xmax >= r.xmax && ymax >= r.ymax;
}

bool rect::intersects(const rect &r) const {
    return !(r.xmin > xmax || r.xmax < xmin || r.ymin > ymax || r.ymax < ymin);
}

rect rect::combine(const rect &a, const rect &b) {
    return rect(std::min(a.xmin, b.xmin),
                std::min(a.ymin, b.ymin),
                std::max(a.xmax, b.xmax),
                std::max(a.ymax, b.ymax));
}

double rect::enlargement_needed(const rect &r) const {
    rect comb = combine(*this, r);
    return comb.area() - this->area();
}

double rect::min_dist_point(const std::pair<double,double>& p) const {
    double dx = 0.0;
    if (p.first < xmin) {
        dx = xmin - p.first;
    }
    else if (p.first > xmax) {
        dx = p.first - xmax;
    }
    
    double dy = 0.0;
    if (p.second < ymin) {
        dy = ymin - p.second;
    }
    else if (p.second > ymax) {
        dy = p.second - ymax;
    }
    
    return std::sqrt(dx*dx + dy*dy);
}