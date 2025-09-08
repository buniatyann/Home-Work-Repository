#include <iterator>
#include <functional>

/*
    Time Complexity of Heap Sort
        Random Access Iterator:
            Worst Case: O(n * log(n))
            Average Case: O(n * log(n))
        Bidirectional Iterator:
            Worst Case: O(n ^ 2)
            Average Case: O(n ^ 2)
    
    Space Complexity of Heap Sort
        Random Access Iterator: O(1)
        Bidirectional Iterator: O(1)
        
*/
namespace heap_sort {
    template <typename Iter_>
    std::size_t left(std::size_t i) {
        return 2 * i + 1;
    }

    template <typename Iter_>
    std::size_t right(std::size_t i) {
        return 2 * i + 2;
    }

    template <typename Iter_>
    std::size_t parent(std::size_t i) {
        return (i - 1) / 2;
    }

    // max_heapify
    template <typename Iter_, typename Comp = std::greater<typename std::iterator_traits<Iter_>::value_type>>
    void max_heapify(Iter_ begin, std::size_t ind, std::size_t heap_size, Comp comp = Comp()) {
        std::size_t l = left<Iter_>(ind);
        std::size_t r = right<Iter_>(ind);
        std::size_t largest = ind;

        if (l < heap_size && comp(*std::next(begin, l), *std::next(begin, largest))) {
            largest = l;
        }
        if (r < heap_size && comp(*std::next(begin, r), *std::next(begin, largest))) {
            largest = r;
        }

        if (largest != ind) {
            std::iter_swap(std::next(begin, largest), std::next(begin, ind));
            max_heapify(begin, largest, heap_size, comp);
        }
    }

    // build_max_heap
    template <typename Iter_, typename Comp = std::greater<typename std::iterator_traits<Iter_>::value_type>>
    void build_max_heap(Iter_ begin, Iter_ end, Comp comp = Comp()) {
        std::size_t heap_size = std::distance(begin, end);
        if (heap_size == 0) return;

        for (std::size_t i = heap_size / 2; i > 0; --i) {
            max_heapify(begin, i - 1, heap_size, comp);
        }

        max_heapify(begin, 0, heap_size, comp);
    }

    // Main sort
    template <typename Iter_, typename Comp = std::greater<typename std::iterator_traits<Iter_>::value_type>>
    void sort(Iter_ begin, Iter_ end, Comp comp = Comp()) {
        if (begin == end) return;

        build_max_heap(begin, end, comp);
        std::size_t heap_size = std::distance(begin, end);

        for (auto it = std::prev(end); it != begin; it = std::prev(it)) {
            std::iter_swap(it, begin);
            --heap_size;
            max_heapify(begin, 0, heap_size, comp);
        }

        if (heap_size > 1) {
            std::iter_swap(begin, std::prev(end));
        }
    }
} // namespace heap_sort

