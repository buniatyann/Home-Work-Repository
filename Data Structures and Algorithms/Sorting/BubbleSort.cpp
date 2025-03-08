#include <algorithm>
#include <vector>
#include <iterator>

/*
    Time complexity
        Random Access Iterator:
            Best Case : O(n)
            Worst Case : O(n ^ 2)
            Average Case : O(n ^ 2)
        Bidirectional Iterator:
            Best Case : O(n)
            Worst Case : O(n ^ 2)
            Average Case : O(n ^ 2)
    Space complexity
        Random Access Iterator:
            O(1) (in-place)
        Bidirectional Iterator:
            O(1) (in-place)
        
*/
template <typename Iter_, typename Comp = std::greater<typename std::iterator_traits<Iter_>::value_type>>
void bubble_sort(Iter_ begin, Iter_ end, Comp comp = Comp()) {
    if (begin == end) return;

    for (Iter_ last = end; last != begin; --last) {
        bool swapped = false;
        
        for (Iter_ it1 = begin, it2 = std::next(begin); it2 != last; ++it1, ++it2) {
            if (comp(*it1, *it2)) {
                std::swap(*it1, *it2);
                swapped = true;
            }
        }
        
        if (!swapped) break; 
    }
}


