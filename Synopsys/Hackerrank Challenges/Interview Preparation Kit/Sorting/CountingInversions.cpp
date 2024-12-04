#include <bits/stdc++.h>

/*
    Time O(n*logn)
    Space O(n)
*/
long merge_and_count(std::vector<int>& arr, std::vector<int>& temp, int left, int mid, int right) {
    int i = left;    // Start of left subarray
    int j = mid + 1; // Start of right subarray
    int k = left;    // Start of merged subarray
    long inv_count = 0;

    while (i <= mid && j <= right) {
        if (arr[i] <= arr[j]) {
            temp[k] = arr[i];
            ++i;
            ++k;
        }
        else {
            // There are mid - i inversions because all elements left to i in the left subarray
            // are greater than arr[j]
            temp[k] = arr[j];
            inv_count += (mid - i + 1);
            ++j;
            ++k;
        }
    }

    // Copy remaining elements of left subarray, if any
    while (i <= mid) {
        temp[k] = arr[i];
        ++i;
        ++k;
    }

    // Copy remaining elements of right subarray, if any
    while (j <= right) {
        temp[k] = arr[j];
        ++j;
        ++k;
    }

    // Copy sorted subarray back into original array
    for (int i = left; i <= right; ++i) {
        arr[i] = temp[i];
    }

    return inv_count;
}

long merge_sort_and_count(std::vector<int>& arr, std::vector<int>& temp, int left, int right) {
    long inv_count = 0;

    if (left < right) {
        int mid = (left + right) / 2;

        inv_count += merge_sort_and_count(arr, temp, left, mid);
        inv_count += merge_sort_and_count(arr, temp, mid + 1, right);
        inv_count += merge_and_count(arr, temp, left, mid, right);
    }

    return inv_count;
}

long countInversions(std::vector<int>& arr) {
    std::vector<int> temp(arr.size());
    
    return merge_sort_and_count(arr, temp, 0, arr.size() - 1);
}