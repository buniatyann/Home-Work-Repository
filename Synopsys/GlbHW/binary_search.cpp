#include <iostream>
#include <vector>
#include <string>
#include <stdexcept>
#include <algorithm>


template <typename T>
int binary_search(std::vector<T>& arr, T value){
    if(arr.empty()){
        throw std::invalid_argument("BAD!!!!!!!!!!!!!!!");
    }
    else if(arr.size() == 1){
        return arr[0] == value ? 0 : -1;
    }

    // for(int i = 1; i < arr.size(); ++i){
    //     if(arr[i] < arr[i - 1]){
    //         throw std::invalid_argument("not sorted!!!!!!!!!!!!");
    //     }
    // }


    unsigned l = 0;
    unsigned r = arr.size() - 1;

    while(l < r){
        unsigned mid = (l + r) >> 1;

        if(arr[mid] == value){
            return mid;
        }
        else if(arr[mid] > value){
            r = mid - 1;
        }
        else{
            l = mid + 1;
        }
    }


    return -1;
}


template <typename _Iterator, typename T>
int binary_search(_Iterator begin, _Iterator end, T value) {
    if (begin == end) {
        throw std::invalid_argument("BAD!!!!!!!!!!!!!!!");
    } else if (std::distance(begin, end) == 1) {
        return *begin == value ? 0 : -1;
    }

    // Check if the range is sorted
    for (_Iterator i = std::next(begin); i != end; ++i) {
        if (*std::prev(i) > *i) {
            throw std::invalid_argument("not sorted!!!!!!!!!!!!");
        }
    }

    _Iterator l = begin;
    _Iterator r = std::prev(end);

    // Binary search loop
    while (l <= r) {
        _Iterator mid = std::next(l, std::distance(l, r) / 2);

        if (*mid == value) {
            return std::distance(begin, mid);
        } else if (*mid > value) {
            r = std::prev(mid);
        } else {
            l = std::next(mid);
        }
    }

    return -1; // Value not found
}
