#include <unordered_map>
#include <vector>
#include <string>
#include <algorithm>

/*
    Time O(m + q)
    Space O(m + q)
    Where m is the number of strings in the strings vector and q is the number of strings in the queries vector.
*/
std::vector<int> matchingStrings(std::vector<std::string> strings, std::vector<std::string> queries) {
    // Create an empty vector to store the results for each query
    std::vector<int> ans;
    
    // Create an unordered_map (hash map) to store the frequency count of each string in 'strings'
    std::unordered_map<std::string, int> dct;
    
    // Loop through the 'strings' vector and populate the frequency map 'dct'
    // Each time a string appears, we increment its count in the map
    for (auto string : strings) {
        ++dct[string];  // Increment the count of the string in the map
    }
    
    // Now process each query in 'queries' to find how many times it appears in 'strings'
    for (auto q : queries) {
        // Check if the query string exists in the map
        if (dct.find(q) != dct.end()) {
            // If found, add the count of the query string to the result vector 'ans'
            ans.push_back(dct[q]);
        }
        else {
            // If the query string is not found, add 0 to the result vector 'ans'
            ans.push_back(0);
        }
    }
    
    // Return the vector 'ans' containing the result for each query
    return ans;
}


/*
    Time O(m*log(m) + q*log(m))
    Space O(m + q)
*/
std::vector<int> matchingStrings(std::vector<std::string> strings, std::vector<std::string> queries) {
    // Sort the input strings to prepare for binary search
    std::sort(strings.begin(), strings.end());
    
    std::vector<int> ans;
    
    // For each query, perform binary search on the sorted 'strings'
    for (const auto& q : queries) {
        // Count occurrences of query 'q' using lower_bound and upper_bound
        auto lower = std::lower_bound(strings.begin(), strings.end(), q);
        auto upper = std::upper_bound(strings.begin(), strings.end(), q);
        
        // The difference between the two iterators gives the count of 'q'
        ans.push_back(upper - lower);
    }
    
    return ans;
}
