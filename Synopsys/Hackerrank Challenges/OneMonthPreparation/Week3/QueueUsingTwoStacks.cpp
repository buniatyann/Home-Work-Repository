#include <iostream>
#include <stack>

/*
    Time O(1) amortized
    Space O(n)
*/
int main() {
    // Declare two stacks
    std::stack<int> first;   
    std::stack<int> last;
    
    int q;
    std::cin >> q;  // Read number of queries
    
    // Process each query
    for (int i = 0; i < q; ++i) {
        int query;
        std::cin >> query;  // Read the query
        
        if (query == 1) {
            // enqueue
            int x;
            std::cin >> x;
            first.push(x);  // Push the element onto the 'first' stack
        }
        else if (query == 2) {
            // dequeue
            if (last.empty()) {
                // If 'last' is empty, transfer elements from 'first' to 'last'
                while (!first.empty()) {
                    last.push(first.top());
                    first.pop();
                }
            }
            
            // Pop the front element from 'last' stack (this is the front of the queue)
            if (!last.empty()) {
                last.pop();
            }
        }
        else if (query == 3) {
            // peek
            if (last.empty()) {
                // If 'last' is empty, transfer elements from 'first' to 'last'
                while (!first.empty()) {
                    last.push(first.top());
                    first.pop();
                }
            }
            
            // Print the front element from 'last' stack (this is the front of the queue)
            if (!last.empty()) {
                std::cout << last.top() << std::endl;
            }
        }
    }
    
    return 0;
}