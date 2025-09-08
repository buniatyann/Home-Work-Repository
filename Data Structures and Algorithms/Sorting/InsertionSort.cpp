#include <vector>
#include <algorithm>
#include <functional>
#include <iterator>

/*
    Time Complexity of Insertion Sort
        Random Access Iterator: O(n ^ 2)
        Bidirectional Iterator: O(n ^ 2)
    
    Space Complexity of Insertion Sort
        Random Access Iterator: O(1)
        Bidirectional Iterator: O(1)
*/

template <typename T>
void insertion_sort(std::vector<T>& vec){
    for (std::size_t i = 1; i < vec.size(); ++i) {
        T key = std::move(vec[i]);
        int j = static_cast<int>(i) - 1; 

        while (j >= 0 && vec[j] > key) { 
            vec[j + 1] = std::move(vec[j]);
            --j;
        }

        vec[j + 1] = std::move(key);
    }
}


template <typename Iter_, typename Comp = std::less<typename std::iterator_traits<Iter_>::value_type>>
void insertion_sort(Iter_ begin, Iter_ end, Comp comp = Comp()) {
    if (begin == end){
        return;
    } 

    for (Iter_ curr = std::next(begin); curr != end; ++curr) {
        typename std::iterator_traits<Iter_>::value_type key = std::move(*curr);
        Iter_ it = curr;

        while (it != begin && comp(key, *std::prev(it))) {
            *it = *std::prev(it); 
            --it;
        }

        *it = std::move(key); 
    }
}
