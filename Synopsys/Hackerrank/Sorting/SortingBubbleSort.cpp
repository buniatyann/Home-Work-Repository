#include <iostream>
#include <vector>
#include <algorithm>

// Time O(n ^ 2) Space O(1)
void countSwaps(std::vector<int> a) {
    int swaps = 0;
    
    for(int i = 0; i < a.size(); ++i){
        for(int j = 0; j < a.size() - 1; ++j){
            if(a[j] > a[j + 1]){
                std::swap(a[j], a[j + 1]);
                swaps++;
            }
        }
    }

    std::cout << "Array is sorted in " << swaps << " swaps." << std::endl;
    std::cout << "First Element: " << a[0] << std::endl;
    std::cout << "Last Element: " << a[a.size() - 1] << std::endl;
}