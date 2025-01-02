#include <iostream>
#include <vector>
#include <algorithm>

/*
    Time O(n)
    Space O(n)
*/
std::string highestValuePalindrome(std::string s, int n, int k) {
    // Convert string to vector of characters for easier manipulation
    std::vector<char> s_vec(s.begin(), s.end());

    // A vector to track whether a change was made during the first pass
    std::vector<bool> diff(n, false);

    // First pass: Make the string a palindrome and track the positions we changed
    for (int i = 0; i < n / 2; ++i) {
        // If characters are not equal, we need to change one of them
        if (s_vec[i] != s_vec[n - 1 - i]) {
            if (k > 0) {
                // Change the smaller character to match the larger one (to minimize cost)
                s_vec[i] = s_vec[n - 1 - i] = std::max(s_vec[i], s_vec[n - 1 - i]);
                k--;  // One change used
                diff[i] = true;  // Mark this position as changed
            } 
            else {
                return "-1";  // If we run out of changes before making a palindrome, return "-1"
            }
        }
    }

    // Second pass: Maximize the palindrome's value by making characters '9' where possible
    for (int i = 0; i < n / 2; ++i) {
        if (s_vec[i] != '9') {
            // If this position was already changed in the first pass, we can convert it to '9'
            if (diff[i] && k > 0) {
                s_vec[i] = s_vec[n - 1 - i] = '9';
                k--;  // One change used
            }
            // If the position wasn't changed in the first pass and we have at least 2 changes left
            else if (!diff[i] && k >= 2) {
                s_vec[i] = s_vec[n - 1 - i] = '9';
                k -= 2;  // Two changes used
            }
        }
    }

    // If the string has an odd length, we can change the middle character to '9' if there's any change left
    if (n % 2 == 1 && k > 0) {
        s_vec[n / 2] = '9';
    }

    // Convert the vector back to string and return the result
    return std::string(s_vec.begin(), s_vec.end());
}
