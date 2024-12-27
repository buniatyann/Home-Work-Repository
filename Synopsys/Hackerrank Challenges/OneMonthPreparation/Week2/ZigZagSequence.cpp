#include <iostream>
#include <vector>
#include <algorithm>


void findZigZagSequence(std::vector<int>& a, int n){
    std::sort(a.begin(), a.end());
    int mid = (n - 1)/2; // instead of (n + 1) / 2;
    std::swap(a[mid], a[n-1]);

    int st = mid + 1;
    int ed = n - 2; // instread of ed = n - 1;
    
    while(st <= ed){
        std::swap(a[st], a[ed]);
        st = st + 1;
        ed = ed - 1; // instread of ed = ed + 1;
    }

    for(int i = 0; i < n; i++){
        if(i > 0){ 
            std::cout << " ";
        }
        else{
            std::cout << a[i];
        }
    }

    std::cout << std::endl;
}