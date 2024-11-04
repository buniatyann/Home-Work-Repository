#include <bits/stdc++.h>

std::vector<int> rotLeft(std::vector<int> a, int d) {
    std::vector<int> ans(a.size());
    int k = 0;
    
    for(int i = d; i < a.size(); ++i){
        ans[k] = a[i];
        k++;
    }
    
    for(int i = 0; i < d; ++i){
        ans[k] = a[i];
        k++;
    }
    
    return ans;
}

// better one
std::vector<int> rotLeft(std::vector<int> a, int d) {
    if (a.size() == 0) return a;  // Handle empty vector
    d = d % a.size();              // Adjust d for larger than n

    std::vector<int> ans(a.size()); // Create the result vector
    // Copy the rotated parts into the result vector
    for (int i = 0; i < a.size(); ++i) {
        ans[i] = a[(i + d) % a.size()];
    }

    return ans; // Return the rotated vector
}