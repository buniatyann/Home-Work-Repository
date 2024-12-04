#include <bits/stdc++.h>

// Time O(n) Space O(n)
// Veranayel
long countTriplets(std::vector<long> arr, long r) {
    std::unordered_map<long long, long long> l_map;  // Map for potential first elements
    std::unordered_map<long long, long long> r_map; // Map for potential third elements

    // Initialize rightMap with counts of all elements
    for (long long item : arr) {
        r_map[item]++;
    }

    long long count = 0;

    // Iterate through the array
    for (size_t i = 0; i < arr.size(); i++) {
        long long mid_t = arr[i];

        // Decrease the count of the midTerm in rightMap
        r_map[mid_t]--;

        // Count of potential first elements (c1)
        long long c1 = 0;
        if (mid_t % r == 0) {
            long long potential_first = mid_t / r;
            if (l_map.find(potential_first) != l_map.end()) {
                c1 = l_map[potential_first];
            }
        }

        // Count of potential third elements (c3)
        long long c3 = 0;
        if (r_map.find(mid_t * r) != r_map.end()) {
            c3 = r_map[mid_t * r];
        }

        // Update total count of triplets
        count += c1 * c3;

        // Update leftMap with the current midTerm
        l_map[mid_t]++;
    }

    return count;
}