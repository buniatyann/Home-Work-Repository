#include <algorithm>
#include <vector>

/*
    Time O(n*log(n))
    Space O(n)
*/
int maxMin(int k, std::vector<int> arr) {
    // Sort the array first. Sorting helps us to easily find the minimum difference
    // between the largest and smallest elements in any subarray of size k.
    std::sort(arr.begin(), arr.end());

    // Initial assumption: the difference between the first k elements is the smallest difference
    int ans = arr[k - 1] - arr[0];
    
    // Iterate through the array and find the minimum difference between
    // the largest and smallest elements in every subarray of size `k`.
    for (int i = 1; i + k <= arr.size(); ++i) {
        // Update the minimum difference by comparing it with the difference of the
        // current subarray (from i to i+k-1).
        ans = std::min(ans, arr[i + k - 1] - arr[i]);
    }
    
    // Return the smallest possible difference found
    return ans;
}