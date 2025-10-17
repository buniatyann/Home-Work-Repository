#ifndef COORD_HPP
#define COORD_HPP

#include <cmath>
#include <type_traits>

template <typename T>
struct Coord_t
{
	static_assert(std::is_arithmetic_v<T>, "type is not arithmetic");

	Coord_t() = default;
	Coord_t(const T& other) : coord(other) {}
    
	bool operator==(const Coord_t& other) const {
        return std::abs(coord - other.coord) <= tolerence;
	}

	bool operator!=(const Coord_t& other) const {
        return !(*this == other);
	}

	operator T&() {
		return coord;
	}

	operator const T& () const {
        return coord;
	}
    
    T coord;
    static constexpr T tolerence 0.0001;
};

#endif // COORD_HPP