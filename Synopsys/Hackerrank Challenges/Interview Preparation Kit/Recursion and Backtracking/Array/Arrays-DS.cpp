#include <bits/stdc++.h>

std::vector<int> reverseArray(std::vector<int> a) {
    int l = 0;
    int r = a.size() - 1;

    
    while (l < r) {
        std::swap(a[l], a[r]);
        l++;
        r--;
    }

    return a; 
}