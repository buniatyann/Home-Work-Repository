#include <iostream>
#include <deque>
#include <vector>
#include <algorithm>

/*
    Time O(q * n), where q is the number of queries and n is the size of the array
    Space O(n), primarily due to the deque used to store indices of the array
    veranayel
*/
std::vector<int> solve(std::vector<int>& arr, std::vector<int>& queries) {
    std::vector<int> result;  // Vector to store the results for each query

    // Iterate over each query (window size)
    for (int d : queries) {
        std::deque<int> l;  // Deque to maintain indices of the array elements
        int m = 0;  // Variable to store the minimum of the maximum values in the sliding window

        // First pass for the first window of size d
        for (int i = d - 1; i >= 0; --i) {
            // Update m to the maximum value seen so far in the first window
            if (m < arr[i]) {
                m = arr[i];
                l.push_front(i);  // Add the index of the current element to the deque from the left
            }
        }

        // Second pass for the remaining elements from d to n
        for (int i = d; i < arr.size(); ++i) {
            // Remove elements from the front of the deque that are out of the current sliding window
            if (l.front() + d <= i) {
                l.pop_front();
            }

            // Remove elements from the back of the deque if the current element is greater
            // This ensures that the deque stores indices of elements in decreasing order
            while (!l.empty() && arr[l.back()] < arr[i]) {
                l.pop_back();
            }

            // Append the current element's index to the deque
            l.push_back(i);

            // Update m to be the minimum of m and the current maximum in the sliding window
            m = std::min(m, arr[l.front()]);
        }

        // Append the result for the current query (window size) to the result vector
        result.push_back(m);
    }

    return result;  // Return the result vector
}
