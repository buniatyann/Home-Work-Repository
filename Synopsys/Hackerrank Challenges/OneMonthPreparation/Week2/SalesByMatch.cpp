// #include <boost/unordered_map.hpp> 
#include <unordered_map>
#include <vector>

// /*
//     Time O(n)
//     Space O(n)
// */
// int sockMerchant(int n, std::vector<int> ar) {
//     boost::unordered_map<int, int> dct;  // Use boost::unordered_map instead of std::unordered_map
    
//     // Count the occurrences of each sock color
//     for (auto i : ar) {
//         ++dct[i];  // Increment the count of the current sock color
//     }
    
//     int ans = 0;
//     // Calculate the number of pairs for each sock color
//     for (auto& [key, value] : dct) {
//         ans += value / 2;  // Add the number of pairs (integer division by 2)
//     }
    
//     return ans;  // Return the total number of pairs
// }

/*
    Time O(n)
    Space O(n)
*/
int sockMerchant(int n, std::vector<int> ar) {
    std::unordered_map<int, int> sock_count;  // Map to store count of each sock color
    int pairs = 0;  // Variable to store the total number of pairs

    // Count the occurrences of each sock color
    for (int sock : ar) {
        sock_count[sock]++;  // Increment the count of this sock color
    }

    // Calculate the number of pairs for each sock color
    for (auto& [color, count] : sock_count) {
        pairs += count / 2;  // Add the number of pairs (integer division by 2)
    }

    return pairs;  // Return the total number of pairs
}


