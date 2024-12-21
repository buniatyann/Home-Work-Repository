#include <vector>
#include <numeric>
#include <string>

/*
    Time O(n)
    Space O(1)
*/
std::string balancedSums(std::vector<int> arr) {
    int total_sum = accumulate(arr.begin(), arr.end(), 0);  // Compute the total sum of the array
    int left_sum = 0;  // Initialize the sum of elements on the left side
    
    for(int i = 0; i < arr.size(); ++i) {
        int right_sum = total_sum - left_sum - arr[i];  // Calculate the sum of elements on the right side
        
        if(left_sum == right_sum) {
            return "YES";  // Balanced split found
        }
        
        left_sum += arr[i];  // Update the left sum with the current element
    }
    
    return "NO";  // No balanced split found
}