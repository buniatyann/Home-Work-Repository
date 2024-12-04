#include <vector>

/*
    Time O(n)
    Space O(1)
*/
int lonelyinteger(std::vector<int> a) {
    // Initialize the answer variable to the first element in the vector
    int ans = a[0];
    
    // Iterate through the rest of the elements in the array
    for(int i = 1; i < a.size(); ++i) {
        // Apply XOR operation between 'ans' and the current element
        ans ^= a[i];
    }
    
    // Return the result, which is the element that appears only once
    return ans;
}
