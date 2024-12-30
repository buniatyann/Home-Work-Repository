#include <vector>
#include <algorithm>
#include <unordered_map>

/*
    Time O(n * log(n))
    Space O(n)
*/
std::vector<int> icecreamParlor(int m, std::vector<int> arr) {
    // Create a vector of pairs where each pair is (ice cream price, original index)
    std::vector<std::pair<int, int>> a;
    for(int i = 0; i < arr.size(); ++i){
        a.push_back({arr[i], i + 1});  // Store each price along with its original index (1-based)
    }
    
    // Sort the vector based on the ice cream prices (first element of the pairs)
    std::sort(a.begin(), a.end());

    int i = 0; // Start from the leftmost index
    int j = arr.size() - 1; // Start from the rightmost index
    
    // Use a two-pointer approach to find two ice creams that sum up to m
    while(i <= j){
        // Check if the sum of prices of two ice creams equals m
        if(a[i].first + a[j].first == m){
            // Return the 1-based indices of the two ice creams (in sorted order)
            if (a[i].second > a[j].second){ 
                return {a[j].second, a[i].second};  // If second index is larger, swap them
            }
            else{
                return {a[i].second, a[j].second};  // Otherwise, return the indices as is
            }
        }
        // If the sum is greater than m, move the right pointer to the left
        else if(a[i].first + a[j].first > m){
            --j;
        }
        // If the sum is less than m, move the left pointer to the right
        else{
            ++i;
        }
    }
    
    // If no solution is found, return {-1, -1}
    return {-1, -1};
}

/*
    Time O(n)
    Space O(n)
*/
std::vector<int> icecreamParlor(int m, std::vector<int> arr) {
    std::unordered_map<int, int> price_map;  // Map to store prices and their corresponding indices
    
    // Iterate through the list of prices
    for(int i = 0; i < arr.size(); ++i) {
        int complement = m - arr[i];  // The complement is the price we're looking for

        // If the complement is already in the map, return the pair of indices
        if(price_map.find(complement) != price_map.end()) {
            // Return the indices (1-based) of the two prices that sum up to m
            return {price_map[complement] + 1, i + 1};  // +1 for 1-based indexing
        }

        // Store the current price and its index in the map
        price_map[arr[i]] = i;
    }

    // If no pair is found, return {-1, -1}
    return {-1, -1};
}
