#include <bits/stdc++.h>

std::vector<int> dynamicArray(int n, const std::vector<std::vector<int>>& queries) {
    // Initialize a 2D vector of empty vectors to hold dynamic arrays
    std::vector<std::vector<int>> l(n);
    // Vector to store the results of type 2 queries
    std::vector<int> result;
    // Variable to keep track of the last answer retrieved
    int lastAnswer = 0;

    // Iterate through each query in the provided queries
    for (const auto& query : queries) {
        // Calculate the index using the XOR of lastAnswer and query[1], then take modulo n
        int a = (lastAnswer ^ query[1]) % n;

        // Check the type of the query
        if (query[0] == 1) {
            // Type 1: Append the value query[2] to the array at index a
            l[a].push_back(query[2]);
        } else if (query[0] == 2) {
            // Type 2: Retrieve the value from the array at index a and specified index query[2]
            // The index is adjusted with modulo to avoid out-of-bounds access
            lastAnswer = l[a][query[2] % l[a].size()];
            // Store the retrieved value in the result vector
            result.push_back(lastAnswer);
        }
    }

    // Return the results collected from type 2 queries
    return result;
}
