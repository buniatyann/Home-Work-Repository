#include <vector>

/*
    Time O(Q), where Q is the total number of querries
    Space O(n + Q1 + Q2), where n is the number of sequences, Q1 is the number of type 1 queries (insertions), and Q2 s the number of type 2 queries (queries)    
*/
std::vector<int> dynamicArray(int n, std::vector<std::vector<int>> queries) {
    int last_answer = 0;  // Initialize the variable to keep track of the last answer
    std::vector<std::vector<int>> arr(n);  // Create an array of vectors to store values for each index
    std::vector<int> ans;  // Result vector to store the output of type 2 queries
    
    // Iterate over each query in the list of queries
    for (auto i : queries) {
        int operation = i[0];  // The type of operation (1 or 2)
        int x = i[1];  // The x value used in both types of operations
        int y = i[2];  // The y value used in the operations
        
        if (operation == 1) {  // Insert y at the position based on x and last_answer
            int ind = (x ^ last_answer) % n;  // Compute the index based on XOR of x and last_answer
            arr[ind].push_back(y);  // Insert y into the vector at index ind
        }
        else {  // Query the value based on x and last_answer, and update last_answer
            int ind = (x ^ last_answer) % n;  // Compute the index in the same way
            last_answer = arr[ind][y % arr[ind].size()];  // Retrieve the element at position y in the vector at index ind
            ans.push_back(last_answer);  // Store the result in the answer vector
        }
    }
    
    return ans;  // Return the list of results for type 2 queries
}
