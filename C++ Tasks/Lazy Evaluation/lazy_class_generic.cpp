#include "lazy_class_generic.h"

// Constructors
template <typename ContainerL, typename ContainerR>
    requires IndexableContainer<ContainerL> && IndexableContainer<ContainerR> &&
             IterableContainer<ContainerL> && IterableContainer<ContainerR>
ContainerPairOps<ContainerL, ContainerR>::ContainerPairOps(const ContainerL& left, const ContainerR& right)
    : left_(left), right_(right) {
    if (left_.size() != right_.size()) {
        throw std::invalid_argument("Containers must have the same size");
    }
}

template <typename ContainerL, typename ContainerR>
    requires IndexableContainer<ContainerL> && IndexableContainer<ContainerR> &&
             IterableContainer<ContainerL> && IterableContainer<ContainerR>
ContainerPairOps<ContainerL, ContainerR>::ContainerPairOps(ContainerL&& left, ContainerR&& right)
    : left_(std::move(left)), right_(std::move(right)) {
    if (left_.size() != right_.size()) {
        throw std::invalid_argument("Containers must have the same size");
    }
}

// Index-based operations
template <typename ContainerL, typename ContainerR>
    requires IndexableContainer<ContainerL> && IndexableContainer<ContainerR> &&
             IterableContainer<ContainerL> && IterableContainer<ContainerR>
typename ContainerPairOps<ContainerL, ContainerR>::T 
ContainerPairOps<ContainerL, ContainerR>::operator+(std::size_t ind) const {
    return left_.at(ind) + right_.at(ind);
}

template <typename ContainerL, typename ContainerR>
    requires IndexableContainer<ContainerL> && IndexableContainer<ContainerR> &&
             IterableContainer<ContainerL> && IterableContainer<ContainerR>
typename ContainerPairOps<ContainerL, ContainerR>::T 
ContainerPairOps<ContainerL, ContainerR>::operator-(std::size_t ind) const {
    return left_.at(ind) - right_.at(ind);
}

template <typename ContainerL, typename ContainerR>
    requires IndexableContainer<ContainerL> && IndexableContainer<ContainerR> &&
             IterableContainer<ContainerL> && IterableContainer<ContainerR>
typename ContainerPairOps<ContainerL, ContainerR>::T 
ContainerPairOps<ContainerL, ContainerR>::operator*(std::size_t ind) const {
    return left_.at(ind) * right_.at(ind);
}

template <typename ContainerL, typename ContainerR>
    requires IndexableContainer<ContainerL> && IndexableContainer<ContainerR> &&
             IterableContainer<ContainerL> && IterableContainer<ContainerR>
typename ContainerPairOps<ContainerL, ContainerR>::T 
ContainerPairOps<ContainerL, ContainerR>::operator/(std::size_t ind) const {
    if (right_.at(ind) == T{}) {
        throw std::domain_error("Zero division error");
    }

    return left_.at(ind) / right_.at(ind);
}

// Accumulation operations
template <typename ContainerL, typename ContainerR>
    requires IndexableContainer<ContainerL> && IndexableContainer<ContainerR> &&
             IterableContainer<ContainerL> && IterableContainer<ContainerR>
typename ContainerPairOps<ContainerL, ContainerR>::T 
ContainerPairOps<ContainerL, ContainerR>::sum_of_elements() const {
    return std::accumulate(left_.begin(), left_.end(), T{}) + 
           std::accumulate(right_.begin(), right_.end(), T{});
}

template <typename ContainerL, typename ContainerR>
    requires IndexableContainer<ContainerL> && IndexableContainer<ContainerR> &&
             IterableContainer<ContainerL> && IterableContainer<ContainerR>
typename ContainerPairOps<ContainerL, ContainerR>::T 
ContainerPairOps<ContainerL, ContainerR>::difference_of_elements() const {
    return std::accumulate(left_.begin(), left_.end(), T{}) - 
           std::accumulate(right_.begin(), right_.end(), T{});
}

// Container operations
template <typename ContainerL, typename ContainerR>
    requires IndexableContainer<ContainerL> && IndexableContainer<ContainerR> &&
             IterableContainer<ContainerL> && IterableContainer<ContainerR>
ContainerL ContainerPairOps<ContainerL, ContainerR>::container_of_sums() const {
    ContainerL result;
    if constexpr (requires { result.reserve(std::size_t{}); }) {
        result.reserve(left_.size());
    }
    
    for (std::size_t i = 0; i < left_.size(); ++i) {
        result.insert(result.end(), this->operator+(i));
    }

    return result;
}

template <typename ContainerL, typename ContainerR>
    requires IndexableContainer<ContainerL> && IndexableContainer<ContainerR> &&
             IterableContainer<ContainerL> && IterableContainer<ContainerR>
ContainerL ContainerPairOps<ContainerL, ContainerR>::container_of_differences() const {
    ContainerL result;
    if constexpr (requires { result.reserve(std::size_t{}); }) {
        result.reserve(left_.size());
    }
    
    for (std::size_t i = 0; i < left_.size(); ++i) {
        result.insert(result.end(), this->operator-(i));
    }
    
    return result;
}

template <typename ContainerL, typename ContainerR>
    requires IndexableContainer<ContainerL> && IndexableContainer<ContainerR> &&
             IterableContainer<ContainerL> && IterableContainer<ContainerR>
ContainerL ContainerPairOps<ContainerL, ContainerR>::container_of_sums_iter() const {
    ContainerL result;
    if constexpr (requires { result.reserve(std::size_t{}); }) {
        result.reserve(left_.size());
    }
    
    auto left_it = left_.begin();
    auto right_it = right_.begin();
    
    while (left_it != left_.end()) {
        result.insert(result.end(), *left_it + *right_it);
        ++left_it;
        ++right_it;
    }

    return result;
}

template <typename ContainerL, typename ContainerR>
    requires IndexableContainer<ContainerL> && IndexableContainer<ContainerR> &&
             IterableContainer<ContainerL> && IterableContainer<ContainerR>
ContainerL ContainerPairOps<ContainerL, ContainerR>::container_of_max() const {
    ContainerL result;
    if constexpr (requires { result.reserve(std::size_t{}); }) {
        result.reserve(left_.size());
    }
    
    std::transform(left_.begin(), left_.end(), right_.begin(), 
                   std::inserter(result, result.end()), 
                   [](const T& a, const T& b) { return std::max(a, b); });
    
    return result;
}

// Generic operation
template <typename ContainerL, typename ContainerR>
    requires IndexableContainer<ContainerL> && IndexableContainer<ContainerR> &&
             IterableContainer<ContainerL> && IterableContainer<ContainerR>
template <typename BinaryOp>
ContainerL ContainerPairOps<ContainerL, ContainerR>::combine_containers(BinaryOp op) const {
    ContainerL result;
    if constexpr (requires { result.reserve(std::size_t{}); }) {
        result.reserve(left_.size());
    }
    
    std::transform(left_.begin(), left_.end(), right_.begin(), 
                   std::inserter(result, result.end()), op);
    
    return result;
}

// Utility methods
template <typename ContainerL, typename ContainerR>
    requires IndexableContainer<ContainerL> && IndexableContainer<ContainerR> &&
             IterableContainer<ContainerL> && IterableContainer<ContainerR>
std::size_t ContainerPairOps<ContainerL, ContainerR>::size() const {
    return left_.size();
}

template <typename ContainerL, typename ContainerR>
    requires IndexableContainer<ContainerL> && IndexableContainer<ContainerR> &&
             IterableContainer<ContainerL> && IterableContainer<ContainerR>
bool ContainerPairOps<ContainerL, ContainerR>::empty() const {
    return left_.empty();
}

// Iterator definitions
template <typename ContainerL, typename ContainerR>
    requires IndexableContainer<ContainerL> && IndexableContainer<ContainerR> &&
             IterableContainer<ContainerL> && IterableContainer<ContainerR>
ContainerPairOps<ContainerL, ContainerR>::iterator::iterator(
    typename ContainerL::const_iterator l, 
    typename ContainerR::const_iterator r) 
    : left_it(l), right_it(r) {}

template <typename ContainerL, typename ContainerR>
    requires IndexableContainer<ContainerL> && IndexableContainer<ContainerR> &&
             IterableContainer<ContainerL> && IterableContainer<ContainerR>
typename ContainerPairOps<ContainerL, ContainerR>::T 
ContainerPairOps<ContainerL, ContainerR>::iterator::operator*() const {
    return *left_it + *right_it;
}

template <typename ContainerL, typename ContainerR>
    requires IndexableContainer<ContainerL> && IndexableContainer<ContainerR> &&
             IterableContainer<ContainerL> && IterableContainer<ContainerR>
typename ContainerPairOps<ContainerL, ContainerR>::iterator& 
ContainerPairOps<ContainerL, ContainerR>::iterator::operator++() {
    ++left_it; 
    ++right_it;
    
    return *this;
}

template <typename ContainerL, typename ContainerR>
    requires IndexableContainer<ContainerL> && IndexableContainer<ContainerR> &&
             IterableContainer<ContainerL> && IterableContainer<ContainerR>
typename ContainerPairOps<ContainerL, ContainerR>::iterator 
ContainerPairOps<ContainerL, ContainerR>::iterator::operator++(int) {
    iterator tmp = *this;
    ++(*this);
    
    return tmp;
}

template <typename ContainerL, typename ContainerR>
    requires IndexableContainer<ContainerL> && IndexableContainer<ContainerR> &&
             IterableContainer<ContainerL> && IterableContainer<ContainerR>
bool ContainerPairOps<ContainerL, ContainerR>::iterator::operator==(const iterator& other) const {
    return left_it == other.left_it;
}

template <typename ContainerL, typename ContainerR>
    requires IndexableContainer<ContainerL> && IndexableContainer<ContainerR> &&
             IterableContainer<ContainerL> && IterableContainer<ContainerR>
bool ContainerPairOps<ContainerL, ContainerR>::iterator::operator!=(const iterator& other) const {
    return !(*this == other);
}

template <typename ContainerL, typename ContainerR>
    requires IndexableContainer<ContainerL> && IndexableContainer<ContainerR> &&
             IterableContainer<ContainerL> && IterableContainer<ContainerR>
typename ContainerPairOps<ContainerL, ContainerR>::iterator 
ContainerPairOps<ContainerL, ContainerR>::begin() const {
    return iterator(left_.begin(), right_.begin());
}

template <typename ContainerL, typename ContainerR>
    requires IndexableContainer<ContainerL> && IndexableContainer<ContainerR> &&
             IterableContainer<ContainerL> && IterableContainer<ContainerR>
typename ContainerPairOps<ContainerL, ContainerR>::iterator 
ContainerPairOps<ContainerL, ContainerR>::end() const {
    return iterator(left_.end(), right_.end());
}