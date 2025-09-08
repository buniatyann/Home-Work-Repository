#include "HeapSort.hpp"

// Parent index
template <typename Iter_, typename Comp>
std::size_t HeapSort<Iter_, Comp>::parent(std::size_t i) {
    return (i - 1) / 2;
}

// Left child index
template <typename Iter_, typename Comp>
std::size_t HeapSort<Iter_, Comp>::left(std::size_t i) {
    return 2 * i + 1;
}

// Right child index
template <typename Iter_, typename Comp>
std::size_t HeapSort<Iter_, Comp>::right(std::size_t i) {
    return 2 * i + 2;
}

// Constructor
template <typename Iter_, typename Comp>
HeapSort<Iter_, Comp>::HeapSort(Iter_ begin, Iter_ end, Comp comp)
    : begin_(begin), end_(end), comp_(comp) {}

// Heapify a subtree rooted at index `ind`
template <typename Iter_, typename Comp>
void HeapSort<Iter_, Comp>::max_heapify(std::size_t ind, std::size_t heap_size) {
    std::size_t l = left(ind);
    std::size_t r = right(ind);
    std::size_t largest = ind;

    if (l < heap_size && comp_(*std::next(begin_, l), *std::next(begin_, largest))) {
        largest = l;
    }

    if (r < heap_size && comp_(*std::next(begin_, r), *std::next(begin_, largest))) {
        largest = r;
    }

    if (largest != ind) {
        std::iter_swap(std::next(begin_, largest), std::next(begin_, ind));
        max_heapify(largest, heap_size);
    }
}

// Build the max heap
template <typename Iter_, typename Comp>
void HeapSort<Iter_, Comp>::build_max_heap() {
    std::size_t heap_size = std::distance(begin_, end_);
    if (heap_size == 0) return;

    for (std::size_t i = heap_size / 2; i > 0; --i) {
        max_heapify(i - 1, heap_size);
    }

    max_heapify(0, heap_size);
}

// Heap Sort Algorithm
template <typename Iter_, typename Comp>
void HeapSort<Iter_, Comp>::sort() {
    if (begin_ == end_){
        return;
    }

    build_max_heap();
    std::size_t heap_size = std::distance(begin_, end_);

    for (auto it = std::prev(end_); it != begin_; it = std::prev(it)) {
        std::iter_swap(it, begin_);
        --heap_size;
        max_heapify(0, heap_size);
    }

    if (heap_size > 1) {
        std::iter_swap(begin_, std::prev(end_));
    }
}
