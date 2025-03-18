#include <algorithm>
#include <iterator>

template <typename Iter_, typename Comp = std::less<typename std::iterator_traits<Iter_>::value_type>>
Iter_ quick_partition(Iter_ low, Iter_ high, Comp comp = Comp()) { // 🔹 Renamed to quick_partition
    using value_type = typename std::iterator_traits<Iter_>::value_type;
    value_type pivot = *std::prev(high);  
    Iter_ i = low;            

    for (Iter_ j = low; j != std::prev(high); ++j) {
        if (comp(*j, pivot)) {
            std::iter_swap(i, j);
            ++i;
        }
    }

    std::iter_swap(i, std::prev(high));
    return i;                  
}

template <typename Iter_, typename Comp = std::less<typename std::iterator_traits<Iter_>::value_type>>
void quick_sort(Iter_ begin, Iter_ end, Comp comp = Comp()) {
    if (std::distance(begin, end) > 1) {
        Iter_ pi = quick_partition(begin, end, comp); 

        quick_sort(begin, pi, comp);            
        quick_sort(std::next(pi), end, comp);          
    }
}