#include <bits/stdc++.h>

//Time O(n) Space O(n)
int sockMerchant(int n, std::vector<int> ar) {
    std::unordered_map<int, int> mp;
    int summ = 0;
    
    for(int i = 0; i < ar.size(); ++i){
        mp[ar[i]]++;
        
        if(mp[ar[i]] != 0){
            summ += mp[ar[i]] / 2;
            
        }
    
        mp[ar[i]] %= 2;
    }
    
    return summ;
}

// Time O(n) Space O(1) 
int sockMerchant(int n, std::vector<int> ar) {
    // Assuming sock types range from 1 to 100 (you can adjust the size as needed)
    std::vector<int> counts(101, 0); // Initialize counts for sock types
    int summ = 0;

    for(int i = 0; i < ar.size(); ++i) {
        counts[ar[i]]++; // Increment count for the sock type

        // Add to the sum the number of pairs formed so far
        if (counts[ar[i]] % 2 == 0) {
            summ++; // We found a pair
        }
    }

    return summ; // Return the total number of pairs
}
