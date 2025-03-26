#include <vector>
#include <algorithm>
#include <iterator>

/*
    Time Complexity: O(n)
    Space Complexity: O(n + k), where k is the maximum value in the input range
*/
template <typename Iter_>
void CountingSort(Iter_ first, Iter_ last) {
    using value_type = typename std::iterator_traits<Iter_>::value_type;
    static_assert(std::is_integral<value_type>::value, "Counting Sort requires an integral type");
    
    value_type k = *std::max_element(first, last);
    auto n = std::distance(first, last);
    if (n <= 1){
        return;
    }
    
    std::vector<value_type> b(n);
    std::vector<size_t> c(k + 1, 0);
    
    for (Iter_ it = first; it != last; ++it) {
        ++c[*it];
    }
    
    for (size_t i = 1; i <= k; ++i) {
        c[i] += c[i - 1];
    }
    
    for (Iter_ it = last - 1; it >= first; --it) {
        b[c[*it] - 1] = *it;
        --c[*it];
    }
    
    std::copy(b.begin(), b.end(), first);
}
