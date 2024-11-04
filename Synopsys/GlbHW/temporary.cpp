//#include <bits/stdc++.h>
#include <iostream>
#include <algorithm>
#include <vector>
#include <list>
#include <string>
#include <iterator>


// KAPUT
template<typename T>
void merge(std::vector<T>& arr, int left, int mid, int right){
    int n1 = mid - left - 1;
    int n2 = right - mid;

    std::vector<T> _left(n1);
    std::vector<T> _right(n2);

    for(int i = 0; i < n1; ++i){
        _left[i] = arr[i];
    }

    for(int i = 0; i < n2; ++i){
        _right[i] = arr[mid + i + 1];
    }

    int i = 0, j = 0, k = left;

    while(i < n1 && j < n2){
        if(_left[i] <= _left[j]){
            arr[k] = _left[i];
            ++i;
        }

        else{
            arr[k] = _right[j];
            j++;
        }
        k++;

    }

    while(i < n1){
        arr[k] = _left[i];
        i++;
        k++;
    }

    while(j < n2){
        arr[k] = _right[j];
        j++;
        k++;
    }
}

template<typename T>
void mergeSort(std::vector<T>& arr, int left, int right) {
    if (left < right) {
        int mid = left + (right - left) / 2;

        // Sort first and second halves
        mergeSort(arr, left, mid);
        mergeSort(arr, mid + 1, right);

        // Merge the sorted halves
        merge(arr, left, mid, right);
    }
}



/*
==================================================================================================================================
==================================================================================================================================
*/


// v1
template<typename Iterator, typename T>
void merge(Iterator begin, Iterator end) {
    Iterator mid = begin + std::distance(begin, end) / 2;
    int n1 = std::distance(mid, begin) + 1;  // Correct allocation size
    int n2 = std::distance(end, mid);

    std::vector<T> _left(n1);
    std::vector<T> _right(n2);

    // Copy data to temporary arrays
    for (int i = 0; i < n1; ++i) {
        _left[i] = *(begin + i); //arr[left + i];  // Corrected index
    }

    for (int i = 0; i < n2; ++i) {
        _right[i] = *(mid + 1 + i); //arr[mid + 1 + i];  // Corrected index
    }

    int i = 0, j = 0, k = left;

    while (i < n1 && j < n2) {
        if (_left[i] <= _right[j]) {  // Compare elements from both arrays
            arr[k] = _left[i];
            ++i;
        } else {
            arr[k] = _right[j];
            ++j;
        }
        ++k;
    }

    // Copy remaining elements of _left, if any
    while (i < n1) {
        arr[k] = _left[i];
        ++i;
        ++k;
    }

    // Copy remaining elements of _right, if any
    while (j < n2) {
        arr[k] = _right[j];
        ++j;
        ++k;
    }
}

template<typename Iterator, typename T>
void mergeSort(Iterator left, Iterator right){//(std::vector<T>& arr, int left, int right) {
    if (left < right) {
        Iterator mid = left + std::distance(left, right) / 2;//left + (right - left) / 2;

        // Sort first and second halves
        mergeSort(left, mid);
        mergeSort(std::next(mid), right);

        // Merge the sorted halves
        merge(left, right);//merge(left, mid, right);
    }
}


// v2

template<typename Iterator>
void merge(Iterator begin, Iterator mid, Iterator end) {
    // Calculate sizes
    auto n1 = std::distance(begin, mid) + 1;  // +1 for the mid element
    auto n2 = std::distance(mid, end);

    std::vector<typename std::iterator_traits<Iterator>::value_type> _left(n1);
    std::vector<typename std::iterator_traits<Iterator>::value_type> _right(n2);

    // Copy data to temporary arrays
    std::copy(begin, mid + 1, _left.begin()); // Including mid element
    std::copy(mid + 1, end, _right.begin());

    Iterator i = _left.begin();
    Iterator j = _right.begin();
    Iterator k = begin;

    // Merge the two temporary arrays back into arr
    while (i < _left.end() && j < _right.end()) {
        if (*i <= *j) {
            *k = *i;
            ++i;
        } else {
            *k = *j;
            ++j;
        }
        ++k;
    }

    // Copy remaining elements of _left, if any
    while (i < _left.end()) {
        *k = *i;
        ++i;
        ++k;
    }

    // Copy remaining elements of _right, if any
    while (j < _right.end()) {
        *k = *j;
        ++j;
        ++k;
    }
}

template<typename Iterator>
void merges_sort(Iterator left, Iterator right) {
    if (std::distance(left, right) > 1) { // Only proceed if there are more than one element
        Iterator mid = left + std::distance(left, right) / 2;

        // Sort first and second halves
        mergeSort(left, mid);
        mergeSort(mid, right);

        // Merge the sorted halves
        merge(left, mid, right);
    }
}


