#include "lazy_class.h"


// Constructor Definitions
template <typename T>
VectorPairOps<T>::VectorPairOps(const std::vector<T>& left, const std::vector<T>& right) 
    : left_(left), right_(right) {
    if (left_.size() != right_.size()) {
        throw std::invalid_argument("Vectors must have the same size");
    }
}

template <typename T>
VectorPairOps<T>::VectorPairOps(std::vector<T>&& left, std::vector<T>&& right) 
    : left_(std::move(left)), right_(std::move(right)) {
    if (left_.size() != right_.size()) {
        throw std::invalid_argument("Vectors must have the same size");
    }
}

// Index-based operations
template <typename T>
T VectorPairOps<T>::element_sum(std::size_t ind) const { 
    return left_.at(ind) + right_.at(ind); 
}

template <typename T>
T VectorPairOps<T>::element_diff(std::size_t ind) const { 
    return left_.at(ind) - right_.at(ind); 
}

template <typename T>
T VectorPairOps<T>::element_product(std::size_t ind) const { 
    return left_.at(ind) * right_.at(ind); 
}

template <typename T>
T VectorPairOps<T>::element_division(std::size_t ind) const {
    if (right_.at(ind) == T{}){ 
        throw std::domain_error("Division by zero");
    }
    
    return left_.at(ind) / right_.at(ind);
}

// Accumulation operations
template <typename T>
T VectorPairOps<T>::sum_of_elements() const {
    return std::accumulate(left_.begin(), left_.end(), T{}) + 
           std::accumulate(right_.begin(), right_.end(), T{});
}

template <typename T>
T VectorPairOps<T>::difference_of_elements() const {
    return std::accumulate(left_.begin(), left_.end(), T{}) - 
           std::accumulate(right_.begin(), right_.end(), T{});
}

// Container operations
template <typename T>
std::vector<T> VectorPairOps<T>::container_of_sums() const {
    std::vector<T> result;
    result.reserve(left_.size());
    std::transform(left_.begin(), left_.end(), right_.begin(), std::back_inserter(result), std::plus<T>{});
    
    return result;
}

template <typename T>
std::vector<T> VectorPairOps<T>::container_of_differences() const {
    std::vector<T> result;
    result.reserve(left_.size());
    std::transform(left_.begin(), left_.end(), right_.begin(), std::back_inserter(result), std::minus<T>{});
    
    return result;
}

template <typename T>
std::vector<T> VectorPairOps<T>::container_of_max() const {
    std::vector<T> result;
    result.reserve(left_.size());
    std::transform(left_.begin(), left_.end(), right_.begin(), std::back_inserter(result), 
                   [](const T& a, const T& b) { 
                       return std::max(a, b); 
                   });
    
    return result;
}

// Utility methods
template <typename T>
std::size_t VectorPairOps<T>::size() const { 
    return left_.size(); 
}

template <typename T>
bool VectorPairOps<T>::empty() const { 
    return left_.empty(); 
}

// Iterator definitions
template <typename T>
VectorPairOps<T>::iterator::iterator(typename std::vector<T>::const_iterator l, 
                                     typename std::vector<T>::const_iterator r) 
    : left_it(l), right_it(r) {}

template <typename T>
T VectorPairOps<T>::iterator::operator*() const { 
    return *left_it + *right_it; 
}

template <typename T>
typename VectorPairOps<T>::iterator& VectorPairOps<T>::iterator::operator++() { 
    ++left_it; 
    ++right_it; 

    return *this; 
}

template <typename T>
typename VectorPairOps<T>::iterator VectorPairOps<T>::iterator::operator++(int) { 
    iterator tmp = *this; 
    ++(*this); 

    return tmp; 
}

template <typename T>
bool VectorPairOps<T>::iterator::operator==(const iterator& other) const { 
    return left_it == other.left_it; 
}

template <typename T>
bool VectorPairOps<T>::iterator::operator!=(const iterator& other) const { 
    return !(*this == other); 
}

// Begin and End Iterator
template <typename T>
typename VectorPairOps<T>::iterator VectorPairOps<T>::begin() const { 
    return iterator(left_.begin(), right_.begin()); 
}

template <typename T>
typename VectorPairOps<T>::iterator VectorPairOps<T>::end() const { 
    return iterator(left_.end(), right_.end()); 
}

