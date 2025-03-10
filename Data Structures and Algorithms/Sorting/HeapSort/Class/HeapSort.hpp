#ifndef HEAP_SORT_HPP
#define HEAP_SORT_HPP

#include <iterator>
#include <functional>

/*
    Time Complexity
        Random Access Iterator:
            Worst Case: O(n * log(n))
            Average Case: O(n * log(n))
        Bidirectional Iterator:
            Worst Case: O(n ^ 2)
            Average Case: O(n ^ 2)
    
    Space Complexity
        Random Access Iterator: O(1)
        Bidirectional Iterator: O(1)
        
*/
template <typename Iter_, typename Comp = std::greater<typename std::iterator_traits<Iter_>::value_type>>
class HeapSort {
public:
    HeapSort(Iter_ begin, Iter_ end, Comp comp = Comp()) : begin_(std::move(begin)), end_(std::move(end)), comp_(std::move(comp)) {}

    void sort();

private:
    Iter_ begin_;
    Iter_ end_;
    Comp comp_;
    
    static std::size_t parent(std::size_t i);
    static std::size_t left(std::size_t i);
    static std::size_t right(std::size_t i);

    void max_heapify(std::size_t ind, std::size_t heap_size);
    void build_max_heap();
};

#endif // HEAP_SORT_HPP
