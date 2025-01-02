#include <vector>
#include <algorithm>
#include <queue>

/*
    Time O(n * log(n))
    Space O(n)
    veranayel
*/
int cookies(int k, std::vector<int> A) {
    // Create a min-heap (priority queue)
    std::priority_queue<int, std::vector<int>, std::greater<int>> pq;
    
    // Push all elements of A into the priority queue
    for (int cookie : A) {
        pq.push(cookie);
    }
    
    int moves = 0;
    
    // While the smallest cookie is less than k, perform the operation
    while (pq.top() < k && pq.size() > 1) {
        // Extract the two smallest elements
        int first = pq.top();
        pq.pop();
        int second = pq.top();
        pq.pop();
        
        // Create a new cookie by combining the two smallest
        int new_cookie = first + 2 * second;
        
        // Insert the new cookie back into the priority queue
        pq.push(new_cookie);
        
        // Increment the number of moves
        moves++;
    }
    
    // If the smallest cookie is still less than k, return -1 (not possible)
    return (pq.top() < k) ? -1 : moves;
}
