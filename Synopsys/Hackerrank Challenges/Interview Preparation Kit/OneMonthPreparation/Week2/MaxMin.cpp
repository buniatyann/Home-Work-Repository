#include <vector>
#include <algorithm>
#include <climits>

/*
    Time O(n * log(n))
    Space O(1) why
*/
int maxMin(int k, std::vector<int>& arr) {
    // Sort the array in ascending order
    std::sort(arr.begin(), arr.end());
    
    // Initialize the minimum difference to a large value
    int minn = INT_MAX;
    
    // Iterate through the array and check all subarrays of size k
    for (int i = 0; i <= arr.size() - k; ++i) {
        // Find the difference between the largest and smallest elements in the window
        minn = std::min(arr[i + k - 1] - arr[i], minn);
    }
    
    return minn;
}