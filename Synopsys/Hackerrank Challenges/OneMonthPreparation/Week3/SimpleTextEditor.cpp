#include <string>
#include <iostream>
#include <algorithm>
#include <stack>

/*
    Time O(n * m)
    Space O(n * m)
    where n is the number of operations and m is the average length of the string at each step
*/
int main() {
    // Initialize an empty string
    std::string s = "";

    // Create a stack to store the history of strings (for undo functionality)
    std::stack<std::string> stack;

    // Push the initial empty string onto the stack (starting state)
    stack.push(s);

    // Read the number of operations
    int n;
    std::cin >> n;

    // Consume the newline character left by cin to ensure proper getline behavior
    std::cin.ignore();

    // Process each operation
    for (int i = 0; i < n; i++) { // Correct the loop to iterate exactly 'n' times
        std::string op;
        std::getline(std::cin, op); // Read the full operation input as a string
        
        // Operation 1: Append a string to the current string 's'
        if (op[0] == '1') {
            // Append the substring starting from index 2 (skipping "1 " prefix)
            s.append(op.substr(2, op.length() - 2));
            // Save the new state of 's' in the stack
            stack.push(s);
        }
        // Operation 2: Delete the last 'k' characters from the string 's'
        else if (op[0] == '2') {
            // Extract the number 'k' (substring starting from index 2)
            int k = std::stoi(op.substr(2, op.length() - 2));
            // Delete the last 'k' characters
            s = s.substr(0, s.length() - k);
            // Save the new state of 's' in the stack
            stack.push(s);
        }
        // Operation 3: Print the character at the 'k'-th position in the string 's'
        else if (op[0] == '3') {
            // Extract the position 'k' (substring starting from index 2)
            int k = std::stoi(op.substr(2, op.length() - 2));
            // Print the character at position 'k' (1-based index, so adjust by subtracting 1)
            std::cout << s[k - 1] << std::endl;
        }
        // Operation 4: Undo the last operation (restore the previous state)
        else if (op[0] == '4') {
            // Pop the top of the stack to revert to the previous state
            stack.pop();
            // Set 's' to the string that was on top of the stack (the state before the last operation)
            s = stack.top();
        }
    }

    return 0;
}
