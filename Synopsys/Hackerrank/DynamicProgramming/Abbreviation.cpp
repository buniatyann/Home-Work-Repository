#include <string>

/*
    Time O(m * n)
    Space O(m * n)
*/
std::string abbreviation(std::string a, std::string b) {
    int n = a.size();  // Length of string a
    int m = b.size();  // Length of string b
    
    // Create a DP table where dp[i][j] indicates whether the first i characters of `a`
    // can form the first j characters of `b`.
    bool dp[n + 1][m + 1];
    
    // Initialize the DP table to false
    for (int i = 0; i <= n; ++i) {
        for (int j = 0; j <= m; ++j) {
            dp[i][j] = false;
        }
    }
    
    // Base case: If both strings are empty, the transformation is trivially possible
    dp[0][0] = true;
    
    // Fill the DP table
    for (int i = 1; i <= n; ++i) {
        for (int j = 0; j <= m; ++j) {
            // If a[i-1] is a lowercase character, we can skip it (delete it)
            // This means if dp[i-1][j] is true, we can also set dp[i][j] to true
            if (std::islower(a[i - 1]) && dp[i - 1][j]) {
                dp[i][j] = true;
            }
            
            // If the current character in a matches the character in b (case-insensitive)
            // We check if dp[i-1][j-1] is true, meaning we can form b[j-1] using a[i-1]
            if (j > 0 && (std::tolower(a[i - 1]) == std::tolower(b[j - 1])) && dp[i - 1][j - 1]) {
                dp[i][j] = true;
            }
        }
    }
    
    // The answer is stored in dp[n][m], which indicates if we can form the entire string b
    // from the entire string a. If it's true, return "YES", otherwise return "NO".
    return dp[n][m] ? "YES" : "NO";
}
