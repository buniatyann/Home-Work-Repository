#include <vector>
#include <iterator>
#include <algorithm>
#include <memory>

/*
    Time Compexity of Merge Sort
        Random Access Iterator:
            Average Case: O(n * log(n))
            Best Case: O(n * log(n))
            Worst Case: O(n * log(n))
        Bidirectional Iterator:
            Average Case: O(n * log(n))
            Best Case: O(n * log(n))
            Worst Case: O(n * log(n))
    Space Comoplexity of Merge Sort
        Random Access Iterator: O(n)
        Bidirectional Iterator: O(n)
*/

template <typename Iter_, typename Compare = std::less<typename std::iterator_traits<Iter_>::value_type>>
void merge(Iter_ begin, Iter_ mid, Iter_ end, Compare comp = Compare()) {
    using value_type = typename std::iterator_traits<Iter_>::value_type;
    using difference_type = typename std::iterator_traits<Iter_>::difference_type;
    
    difference_type n1 = std::distance(begin, mid);
    difference_type n2 = std::distance(mid, end);
    
    std::vector<value_type> left(n1, value_type());
    std::vector<value_type> right(n2, value_type());
    
    std::copy(begin, mid, left.begin());
    std::copy(mid, end, right.begin());
    
    auto left_it = left.begin();
    auto right_it = right.begin();
    auto arr_it = begin;
    
    while (left_it != left.end() && right_it != right.end()) {
        if (comp(*left_it, *right_it)) {
            *arr_it = *left_it;
            ++left_it;
        } 
        else {
            *arr_it = *right_it;
            ++right_it;
        }

        std::advance(arr_it, 1);
    }
    
    while (left_it != left.end()) {
        *arr_it = *left_it;
        ++left_it;
    
        std::advance(arr_it, 1);
    }
    
    while (right_it != right.end()) {
        *arr_it = *right_it;
        ++right_it;
    
        std::advance(arr_it, 1);
    }
}

template <typename Iter_, typename Compare = std::less<typename std::iterator_traits<Iter_>::value_type>>
void merge_sort(Iter_ begin, Iter_ end, Compare comp = Compare()) {
    using difference_type = typename std::iterator_traits<Iter_>::difference_type;
    difference_type dist = std::distance(begin, end);
    if (dist <= 1) {
        return;
    }
    
    Iter_ mid = begin;
    std::advance(mid, dist / 2);
    
    merge_sort(begin, mid, comp);
    merge_sort(mid, end, comp);
    
    merge(begin, mid, end, comp);
}
