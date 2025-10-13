#ifndef COORD_HPP
#define COORD_HPP

#include <type_traits>
#include <cmath>

template <typename T>
struct coord_t {
    T coord;
    static constexpr double TOLERANCE = 0.0001;
    bool operator==(coord_t rhs) const {
        return std::abs(coord-rhs.coord) < TOLERANCE; // will work normally for integer types
    }

    bool operator!=(coord_t rhs) const { // arandz const & i poxancelu depqum compilery vaxenuma optimizacia ani manavand inline functionnnerum, isk const & i depqum karogha copy ani 
        return !(*this == &rhs);
    }

    operator T&() {
        return coord;
    }

    operator const T&() const {
        return coord;
    }

    // operator double&() {
    //     return static_cast<double>(coord);
    // }

    // operator double&() const {
    //     return static_cast<double>(coord);
    // }
};


#endif // COORD_HPP