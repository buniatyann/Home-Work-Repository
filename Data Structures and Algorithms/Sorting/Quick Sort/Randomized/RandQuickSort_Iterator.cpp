#include <algorithm>
#include <iterator>
#include <random>

template <typename Iter_, typename Comp = std::greater<typename std::iterator_traits<Iter_>::value_type>>
Iter_ custom_partition(Iter_ first, Iter_ last, Comp comp = Comp()) {
    using value_type = typename std::iterator_traits<Iter_>::value_type;
    value_type pivot = *std::prev(last);
    Iter_ i = first;
    
    for (Iter_ j = first; j != std::prev(last); ++j) {
        if (comp(*j, pivot)) {
            std::iter_swap(i, j);
            ++i;
        }
    }

    std::iter_swap(i, std::prev(last));
    return i;
}

std::size_t get_random_number(std::size_t l, std::size_t r) {
    static std::random_device rd;
    static std::mt19937 gen(rd());
    std::uniform_int_distribution<std::size_t> dist(l, r - 1);
    return dist(gen);
}

template <typename Iter_, typename Comp = std::greater<typename std::iterator_traits<Iter_>::value_type>>
Iter_ randomized_partition(Iter_ first, Iter_ last, Comp comp = Comp()) {
    auto distance = std::distance(first, last);
    if (distance <= 1) return first;

    std::size_t random_idx = get_random_number(0, distance - 1);
    Iter_ pivot_it = first;
    std::advance(pivot_it, random_idx);
    std::iter_swap(pivot_it, std::prev(last));

    return custom_partition(first, last, comp);  
}

template <typename Iter_, typename Comp = std::greater<typename std::iterator_traits<Iter_>::value_type>>
void randomized_quick_sort(Iter_ first, Iter_ last, Comp comp = Comp()) {
    if (std::distance(first, last) > 1) {
        Iter_ q = randomized_partition(first, last, comp);
        
        randomized_quick_sort(first, q, comp);
        randomized_quick_sort(std::next(q), last, comp);
    }
}
