#include <vector>

/*
    Time O(n)
    Space O(n)
*/
std::vector<int> countingSort(std::vector<int> arr) {
    // Create a vector to store the frequency of each element in the input array.
    // The size of the vector is 100 assuming input values range from 0 to 99.
    std::vector<int> ans(100);
    
    // Iterate over each element in the input array
    for(auto i : arr) {
        // Increment the count of the value 'i' in the ans vector
        ++ans[i];
    }
    
    // Return the frequency distribution of the elements
    return ans;
}
