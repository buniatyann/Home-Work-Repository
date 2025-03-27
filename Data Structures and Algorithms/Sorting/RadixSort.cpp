#include <algorithm>
#include <iterator>
#include <type_traits>

template <typename Iter_>
void Modified_Counting_Sort(Iter_ first, Iter_ last, std::size_t exp) {
    using value_type = typename std::iterator_traits<Iter_>::value_type;
    static_assert(std::is_integral<value_type>::value, "Counting Sort requires an integral type");
    
    auto n = std::distance(first, last);
    if (n <= 1) return;
    
    std::vector<value_type> b(n);
    std::vector<size_t> c(10, 0);
    
    for (Iter_ it = first; it != last; ++it) {
        ++c[(*it / exp) % 10];
    }
    
    for (size_t i = 1; i < 10; ++i) {
        c[i] += c[i - 1];
    }
    
    for (Iter_ it = last - 1; it >= first; --it) {
        size_t digit = (*it / exp) % 10;
        b[c[digit] - 1] = *it;
        --c[digit];
    }
    
    std::copy(b.begin(), b.end(), first);
}

/*
    Time Complexity: O(d * (n + k)), where d is the number of times that counting sort is called
    Space Complexity: O(n)
*/
template <typename Iter_>
void RadixSort(Iter_ begin, Iter_ end) {
    using value_type = typename std::iterator_traits<Iter_>::value_type;
    static_assert(std::is_integral<value_type>::value, "Sortable type must be integral type");
    
    std::size_t size = std::distance(begin, end);
    if (size <= 1) return;
    
    value_type maxx = *std::max_element(begin, end);
    if (maxx < 0) return;
    
    for (std::size_t exp = 1; maxx / exp > 0; exp *= 10) {
        Modified_Counting_Sort(begin, end, exp);
    }
}
