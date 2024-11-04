#include <bits/stdc++.h>

/*
    Time O(m * n)
    Space O(m * n)
    Veranayel
*/
int commonChild(std::string s1, std::string s2) {
    // Get the lengths of the input strings
    int m = s1.length();
    int n = s2.length();
    
    // Create a 2D vector to store the lengths of the longest common subsequence
    // Initialize all elements to 0
    std::vector<std::vector<int>> L(m + 1, std::vector<int>(n + 1, 0));
    
    // Iterate over each character of both strings
    for (int i = 0; i <= m; ++i) {
        for (int j = 0; j <= n; ++j) {
            
            // If we're at the first row or first column, set L[i][j] to 0
            // This represents the base case where one of the strings is empty
            if (i == 0 || j == 0) {
                L[i][j] = 0;
            }
            // If the characters at the current positions of both strings match,
            // we add 1 to the value from the previous positions in both strings
            else if (s1[i - 1] == s2[j - 1]) {
                L[i][j] = L[i - 1][j - 1] + 1;
            }
            // If the characters do not match, take the maximum value from either
            // the cell above (L[i - 1][j]) or the cell to the left (L[i][j - 1])
            else {
                L[i][j] = std::max(L[i - 1][j], L[i][j - 1]);    
            }
        }
    }
    
    // The value in the bottom-right cell of the matrix is the length of the 
    // longest common subsequence of the two strings
    return L[m][n];
}
