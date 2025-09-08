#include <vector>
#include <algorithm>
#include <random>

template <typename T, typename Comp = std::greater<T>>
std::size_t partition(std::vector<T>& arr, std::size_t low, std::size_t high, Comp comp = Comp()) {
    T pivot = arr[high];   
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

std::size_t get_random_number(std::size_t l, std::size_t r) {
    static std::random_device rd;  
    static std::mt19937 gen(rd());
    std::uniform_int_distribution<std::size_t> dist(l, r - 1);

    return dist(gen);
}

template <typename T, typename Comp = std::greater<T>>
std::size_t randomized_partition(std::vector<T>& arr, std::size_t low, std::size_t high, Comp comp = Comp()) {
    std::size_t i = getRandomNumber(low, high);
    std::swap(arr[i], arr[high]);  

    return partition(arr, low, high, comp);
}

template <typename T, typename Comp = std::greater<T>>
void randomized_quick_sort(std::vector<T>& arr, std::size_t low, std::size_t high, Comp comp = Comp()) {
    if (low < high) {
        std::size_t q = randomized_partition(arr, low, high, comp);

        if (q > 0) randomized_quick_sort(arr, low, q - 1, comp);
        randomized_quick_sort(arr, q + 1, high, comp);
    }
}
