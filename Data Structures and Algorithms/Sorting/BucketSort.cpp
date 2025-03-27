#include <vector>
#include <algorithm>
#include <iterator>
#include <functional>

/*
    Time Complexity:
        Best Case: O(n)
        Average Case: O(n)
        Worst Case: O(n ^ 2)
    Space Complexity:
        For all cases: O(n)
*/
template <typename Iter_, typename Comp = std::less<typename std::iterator_traits<Iter_>::value_type>>
void bucket_sort(Iter_ begin, Iter_ end, Comp comp = Comp()) {
    using value_type = typename std::iterator_traits<Iter_>::value_type;

    auto size = std::distance(begin, end);
    if (size <= 1){
        return;
    }

    std::vector<std::vector<value_type>> buckets(size);

    auto [min_it, max_it] = std::minmax_element(begin, end, comp);
    value_type min_val = *min_it;
    value_type max_val = *max_it;
    value_type range = max_val - min_val;

    if (range == 0){
        return;
    }
    for (Iter_ it = begin; it != end; ++it) {
        std::size_t bucket_idx = static_cast<std::size_t>(
            (*it - min_val) * (size - 1) / range
        );
        
        buckets[bucket_idx].push_back(*it);
    }

    for (auto& bucket : buckets) {
        insertion_sort(bucket.begin(), bucket.end(), comp);
    }

    Iter_ current = begin;
    for (const auto& bucket : buckets) {
        for (const auto& value : bucket) {
            *current = value;
            ++current;
        }
    }
}
