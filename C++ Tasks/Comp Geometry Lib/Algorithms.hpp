#ifndef ALGORITHMS_HPP
#define ALGORITHMS_HPP

#include "Point.hpp"
#include "Segment.hpp"
#include "Line.hpp"
#include "Ray.hpp"

namespace algo {
/*
================================================================================================================
                                Intersection of 2 2D segments
================================================================================================================
*/
    // Returns true if the sequence of points A -> B -> C makes a counter-clockwise turn
    /*template <typename T, std::size_t N>
    bool isCounterClockwiseTurn(const Point<T, N>& A, const Point<T, N>& B, const Point<T, N>& C) {
        return Vector<T, N>(A, B).cross(Vector<T, N>(A, C)) > 0;
    }*/

    template <typename T, std::size_t N>
    bool intersect(const Segment<T, N>& seg1, const Segment<T, N>& seg2) {
        // Let segment 1 be AB, and segment 2 be CD
        auto A = seg1.p1_;
        auto B = seg1.p2_;
        auto C = seg2.p1_;
        auto D = seg2.p2_;

        // Lambda to check if the turn A -> B -> C is counter-clockwise
        auto isCounterClockwiseTurn = [](const Point<T, N>& A, const Point<T, N>& B, const Point<T, N>& C) -> bool {
            return Vector<T, N>(A, B).cross(Vector<T, N>(A, C)) > 0;
        };

        // Two segments AB and CD intersect if and only if:
        // - Points C and D are on different sides of segment AB
        // - Points A and B are on different sides of segment CD
        return (isCounterClockwiseTurn(A, C, D) != isCounterClockwiseTurn(B, C, D)) &&
            (isCounterClockwiseTurn(A, B, C) != isCounterClockwiseTurn(A, B, D));
    }

/*
================================================================================================================
                                Intersection of 2 2D Rays
================================================================================================================
*/
    template <typename T, std::size_t N>
    bool intersect(const Ray<T, N>& ray1, const Ray<T, N>& ray2) {
        auto epsilon = 1e-9;

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

/*
================================================================================================================
                                Intersection of 2 2D Lines
================================================================================================================
*/
    template <typename T, std::size_t N>
    bool intersect(const Line<T, N>& line1, const Line<T, N>& line2) {
        using Vector = Vector<T, N>;
        auto A = line1.p1_;
        auto B = line1.p2_;
        auto C = line2.p1_;
        auto D = line2.p2_;
        Vector BA(A, B);
        Vector DC(C, D);
        Vector CA(A, C);

        // if BA and DC are parallel
        if (BA.cross(DC) == 0) {
            // they're parallel, check if they are colinear
            return BA.cross(CA) == 0;
        }

        return true; // not parallel => they must intersect
    }

/*
================================================================================================================
                                Intersection of 2D line and 2D segment
================================================================================================================
*/
    template <typename T, std::size_t N>
    bool intersect(const Line<T, N>& AB, const Segment<T, N>& CD) {
        //using Vector = Vector<T, N>;
        //// Line is represented by 2 points A and B
        //auto A = AB.p1_;
        //auto B = AB.p2_;
        //// Segment is represented by 2 points C and D
        //auto C = CD.p1_;
        //auto D = CD.p2_;

        //Vector BA(A, B); // directional vector of the line
        //Vector CA(A, C); // C -> A
        //Vector DC(C, D); // C -> D

        ////return isCounterClockwiseTurn<T, N>(A, B, C) ^ isCounterClockwiseTurn<T, N>(A, B, D); for further checking ??

        //auto crossBAC = CA.cross(BA); // cross product of BA and CA
        //auto crossDAC = CA.cross(DA); // cross product of DA and CA
        //if (crossBAC == 0 and crossDAC == 0) {
        //    return true; // either points of the segment lies on the line
        //}
        //else if (crossBAC == 0 or crossDAC == 0 or (crossBAC * crossDAC) < 0) {
        //    return true; // segment touches or crosses the line
        //}

        //return false;
        using Vector = Vector<T, N>;

        auto A = AB.p1_;
        auto B = AB.p2_;
        auto C = CD.p1_;
        auto D = CD.p2_;

        Vector AB_vec(A, B);
        Vector AC(A, C);
        Vector AD(A, D);

        auto cross1 = AB_vec.cross(AC);
        auto cross2 = AB_vec.cross(AD);

        // Case 1: segment lies entirely on the line
        if (cross1 == 0 && cross2 == 0) {
            return true;
        }

        // Case 2: segment straddles the line (or touches it)
        return (cross1 == 0 || cross2 == 0 || (cross1 * cross2) < 0);
    }

    template <typename T, std::size_t N>
    bool intersect(const Segment<T, N>& CD, const Line<T, N>& AB) {
        //using Vector = Vector<T, N>;
        //// Line is represented by 2 points A and B
        //auto A = AB.p1_;
        //auto B = AB.p2_;
        //// Segment is represented by 2 points C and D
        //auto C = CD.p1_;
        //auto D = CD.p2_;

        //Vector BA(A, B); // directional vector of the line
        //Vector CA(A, C); // C -> A
        //Vector DC(C, D); // C -> D

        ////return isCounterClockwiseTurn<T, N>(A, B, C) ^ isCounterClockwiseTurn<T, N>(A, B, D); for further checking ??

        //auto crossBAC = CA.cross(BA); // cross product of BA and CA
        //auto crossDAC = CA.cross(DC); // cross product of DA and CC
        //if (crossBAC == 0 and crossDAC == 0) {
        //    return true; // either points of the segment lies on the line
        //}
        //else if (crossBAC == 0 or crossDAC == 0 or (crossBAC * crossDAC) < 0) {
        //    return true; // segment touches or crosses the line
        //}

        //return false;
        using Vector = Vector<T, N>;

        auto A = AB.p1_;
        auto B = AB.p2_;
        auto C = CD.p1_;
        auto D = CD.p2_;

        Vector AB_vec(A, B);
        Vector AC(A, C);
        Vector AD(A, D);

        auto cross1 = AB_vec.cross(AC);
        auto cross2 = AB_vec.cross(AD);

        // Case 1: segment lies entirely on the line
        if (cross1 == 0 && cross2 == 0) {
            return true;
        }

        // Case 2: segment straddles the line (or touches it)
        return (cross1 == 0 || cross2 == 0 || (cross1 * cross2) < 0);
    }

/*
================================================================================================================
                                Intersection of 2D ray and line
================================================================================================================
*/
template <typename T, std::size_t N>
bool intersect(const Ray<T, N>& AB, const Line<T, N>& CD) {
    using Vector = Vector<T, N>;
    auto A = AB.p1_; // start point of a ray
    auto B = AB.p2_; // end point of a ray
    auto C = CD.p1_;
    auto D = CD.p2_;

    Vector BA(A, B); // A -> B
    Vector DC(C, D); // C -> D
    Vector CA(A, C); // A -> C

    auto denom = DC.cross(BA);
    // DC and BA are parallel (could be collinear or disjoint)
    if (denom == 0) {
        return BA.cross(CA) == 0; // Collinear => intersect (means C lies on a line), otherwise false
    }

    auto s = CA.cross(BA) / denom;
    return s >= 0;
}

template <typename T, std::size_t N>
bool intersect(const Line<T, N>& CD, const Ray<T, N>& AB) {
    using Vector = Vector<T, N>;
    auto A = AB.p1_; // start point of a ray
    auto B = AB.p2_; // end point of a ray
    auto C = CD.p1_;
    auto D = CD.p2_;

    Vector BA(A, B); // A -> B
    Vector DC(C, D); // C -> D
    Vector CA(A, C); // A -> C

    auto denom = DC.cross(BA);
    // DC and BA are parallel (could be collinear or disjoint)
    if (denom == 0) {
        return BA.cross(CA) == 0; // Collinear => intersect (means C lies on a line), otherwise false
    }

    auto s = CA.cross(BA) / denom;
    return s >= 0;
}

/*
================================================================================================================
                                Intersection of 2D ray and line
================================================================================================================
*/

    template <typename T, std::size_t N>
    bool intersect(const Segment<T, N>& AB, const Ray<T, N>& CD) {
        using Vector = Vector<T, N>;
        auto A = AB.p1_;
        auto B = AB.p2_;
        auto C = CD.p1_;
        auto D = CD.p2_;

        Vector BA(A, B); // A -> B
        Vector DC(C, D); // C -> D
        Vector CA(A, C); // A -> C

        auto denum = DC.cross(BA);
        if (denum == 0) {
            // Ray and Segment are parallel
            if (DC.cross(CA) != 0) {
                return false; // not colinear
            }

            // they are parallel, check projection overlap
            auto rayDot = DC.dot(DC);
            auto t0 = CA.dot(DC) / rayDot;
            auto t1 = Vector(C, B).dot(DC) / rayDot;

            return (t1 >= 0 || t0 >= 0) && (std::max(t0, t1) > std::min(t0, t1));
        }

        auto t = CA.cross(DC) / denum;
        auto u = CA.cross(BA) / denum;

        return (t >= 0 && t <= 1) && (u >= 0);
    }

    template <typename T, std::size_t N>
    bool intersect(const Ray<T, N>& CD, const Segment<T, N>& AB) {
        using Vector = Vector<T, N>;
        auto A = AB.p1_;
        auto B = AB.p2_;
        auto C = CD.p1_;
        auto D = CD.p2_;

        Vector BA(A, B); // A -> B
        Vector DC(C, D); // C -> D
        Vector CA(A, C); // A -> C

        auto denum = DC.cross(BA);
        if (denum == 0) {
            // Ray and Segment are parallel
            if (DC.cross(CA) != 0) {
                return false; // not colinear
            }

            // they are parallel, check projection overlap
            auto rayDot = DC.dot(DC);
            auto t0 = CA.dot(DC) / rayDot;
            auto t1 = Vector(C, B).dot(DC) / rayDot;

            return (t1 >= 0 || t0 >= 0) && (std::max(t0, t1) > std::min(t0, t1));
        }

        auto t = CA.cross(DC) / denum;
        auto u = CA.cross(BA) / denum;

        return (t >= 0 && t <= 1) && (u >= 0);
    }

} // namespace algo

#endif // ALGORITHMS_HPP