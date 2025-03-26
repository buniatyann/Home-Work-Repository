#include <vector>
#include <algorithm>
#include <iterator>
#include <type_traits>

template <typename T, typename Comp = std::greater<T>>
std::size_t partition(std::vector<T>& arr, std::size_t low, std::size_t high, Comp comp = Comp()) {
    T pivot = arr[high - 1];   
    std::size_t i = (low - 1);     
    for (std::size_t j = low; j < high; j++) {
        if (!comp(arr[j], pivot)) {  
            ++i;    
            std::swap(arr[i], arr[j]);
        }
    }

    std::swap(arr[i + 1], arr[high]);
    return (i + 1);
}

/*
    Time Complexity:
        Best and Average Case: O(n * log(n))
        Worst Case: O(n ^ 2)
    Space Complexity:
        Best and Average Case: O(log(n))
        Worst Case: O(n)
*/
template <typename T, typename Comp = std::greater<T>>
void quick_sort(std::vector<T>& arr, std::size_t low, std::size_t high, Comp comp = Comp()) {
    if (low < high) {
        std::size_t pi = partition(arr, low, high, comp);  

        quick_sort(arr, low, pi - 1, comp);
        quick_sort(arr, pi + 1, high, comp);
    }
}

