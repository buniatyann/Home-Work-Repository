#include <iostream>
#include <vector>
#include <algorithm>

class Heap {
public:
    // Constructor to initialize the heap (an empty vector)
    Heap() {}

    // Insert a value into the heap, maintaining sorted order.
    /*
        Time O(n)
        Space O(1)
    */
    void insert(int x) {
        // std::lower_bound finds the first position where x can be inserted while keeping the vector sorted.
        // The time complexity for lower_bound is O(log n) to find the correct position.
        // After finding the correct position, std::vector::insert inserts the value, which is O(n) due to shifting elements.
        auto pos = std::lower_bound(heap.begin(), heap.end(), x);
        heap.insert(pos, x);
    }

    // Delete a value from the heap. If the value is present, it will be removed.
    /*
        Time O(n)
        Space O(1)
    */
    void del(int x) {
        // std::find searches for the element in the vector, which has O(n) time complexity.
        // If the element is found, std::vector::erase will remove it, which also takes O(n) in the worst case.
        auto it = std::find(heap.begin(), heap.end(), x);
        if (it != heap.end()) {
            heap.erase(it); // Remove the element found by find.
        }
    }

    // Print the minimum value in the heap (first element in a sorted vector).
    /*
        Time O(1)
        Space O(1)
    */
    void print_min() {
        // If the heap is not empty, the minimum value will be at the front of the sorted vector.
        if (!heap.empty()) {
            std::cout << heap.front() << std::endl;
        }
    }

private:
    // Private member: A vector that stores the heap elements in sorted order.
    std::vector<int> heap;
};

int main() {
    int q;
    std::cin >> q; // Read the number of queries.
    Heap hp; // Create an instance of the Heap class.
    
    for (int i = 0; i < q; ++i) {
        int query;
        std::cin >> query; // Read the type of query (1: insert, 2: delete, 3: print minimum).
        
        if (query == 1) { // Insert query
            int x;
            std::cin >> x; // Read the value to be inserted.
            hp.insert(x); // Insert the value into the heap.
        } else if (query == 2) { // Delete query
            int x;
            std::cin >> x; // Read the value to be deleted.
            hp.del(x); // Delete the value from the heap.
        } else { // Print minimum query
            hp.print_min(); // Print the minimum value in the heap.
        }
    }

    return 0; // End of the program.
}
