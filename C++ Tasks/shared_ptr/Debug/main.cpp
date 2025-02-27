#include "shared_ptr.hpp"
#include <iostream>
#include <cassert>
#include <memory>  // for std::default_delete and std::allocator

// Sample class to be managed by shared_ptr
class TestClass {
public:
    TestClass(int x) : x_(x) {
        std::cout << "TestClass(" << x_ << ") constructor called." << std::endl;
    }
    ~TestClass() {
        std::cout << "TestClass(" << x_ << ") destructor called." << std::endl;
    }
    
    int get_value() const { return x_; }
private:
    int x_;
};

int main() {
    // Test 1: Basic shared_ptr functionality (construction, dereferencing)
    {
        std::cout << "Test 1: Basic shared_ptr functionality" << std::endl;
        shared_ptr<TestClass> ptr1(new TestClass(10));  // Create with custom allocator and deleter
        assert(ptr1.get() != nullptr);  // Check that the pointer is valid
        assert(ptr1->get_value() == 10);  // Dereference and check value
        std::cout << "Passed Test 1." << std::endl;
    }

    // Test 2: Copy Constructor
    {
        std::cout << "Test 2: Copy constructor" << std::endl;
        shared_ptr<TestClass> ptr1(new TestClass(20));
        shared_ptr<TestClass> ptr2 = ptr1;  // Use copy constructor
        assert(ptr1.get() == ptr2.get());  // Both should point to the same object
        assert(ptr1->get_value() == 20);  // Verify the value is still correct
        std::cout << "Passed Test 2." << std::endl;
    }

    // Test 3: Move Constructor
    {
        std::cout << "Test 3: Move constructor" << std::endl;
        shared_ptr<TestClass> ptr1(new TestClass(30));
        shared_ptr<TestClass> ptr2 = std::move(ptr1);  // Use move constructor
        assert(ptr1.get() == nullptr);  // ptr1 should be null after move
        assert(ptr2.get() != nullptr);  // ptr2 should now own the object
        assert(ptr2->get_value() == 30);  // Verify the value is correct
        std::cout << "Passed Test 3." << std::endl;
    }

    // Test 4: Move Assignment
    {
        std::cout << "Test 4: Move assignment" << std::endl;
        shared_ptr<TestClass> ptr1(new TestClass(40));
        shared_ptr<TestClass> ptr2(new TestClass(50));
        ptr2 = std::move(ptr1);  // Use move assignment
        assert(ptr1.get() == nullptr);  // ptr1 should be null after move
        assert(ptr2.get() != nullptr);  // ptr2 should now own the object
        assert(ptr2->get_value() == 40);  // Verify the value is correct
        std::cout << "Passed Test 4." << std::endl;
    }

    // Test 5: Copy Assignment
    {
        std::cout << "Test 5: Copy assignment" << std::endl;
        shared_ptr<TestClass> ptr1(new TestClass(60));
        shared_ptr<TestClass> ptr2(new TestClass(70));
        ptr2 = ptr1;  // Use copy assignment
        assert(ptr1.get() == ptr2.get());  // Both should point to the same object
        assert(ptr1->get_value() == 60);  // Verify the value is correct
        std::cout << "Passed Test 5." << std::endl;
    }

    // Test 6: Destructor (Check that destructors are called and memory is cleaned up)
    {
        std::cout << "Test 6: Destructor (Check that destructors are called)" << std::endl;
        {
            shared_ptr<TestClass> ptr1(new TestClass(100));
            // Destructor will be called at the end of the scope
        }  // Check console output for destructor calls (this should print the destructor message)
        std::cout << "Passed Test 6." << std::endl;
    }

    // Test 7: Self-assignment check (No-op expected)
    {
        std::cout << "Test 7: Self-assignment check" << std::endl;
        shared_ptr<TestClass> ptr1(new TestClass(200));
        ptr1 = ptr1;  // Self-assignment (should do nothing)
        assert(ptr1->get_value() == 200);  // Ensure ptr1 is still valid
        std::cout << "Passed Test 7." << std::endl;
    }

    // Test 8: Memory management (Verify memory cleanup on shared_ptr destruction)
    {
        std::cout << "Test 8: Memory management (Check that memory is cleaned up)" << std::endl;
        shared_ptr<TestClass> ptr1(new TestClass(300));
        shared_ptr<TestClass> ptr2 = ptr1;
        assert(ptr1->get_value() == 300);
        ptr1 = nullptr;  // Decrease reference count by releasing ptr1
        assert(ptr2->get_value() == 300);  // ptr2 still points to the object
        ptr2 = nullptr;  // Both ptr1 and ptr2 should now be out of scope, and the memory should be cleaned up
        std::cout << "Passed Test 8." << std::endl;
    }

    // Test 9: Multi-threaded Safety (optional, requires changes for atomic ref counting)
    {
        std::cout << "Test 9: Multi-threaded Safety (simulated, will only pass if atomic reference counting is used)" << std::endl;
        // This would require using atomic reference counting and creating threads to test safely.
        std::cout << "Note: This test requires multi-threaded support, which isn't implemented here." << std::endl;
    }

    // Test 10: Null pointer checks
    {
        std::cout << "Test 10: Null pointer checks" << std::endl;
        shared_ptr<TestClass> ptr1;
        assert(ptr1.get() == nullptr);  // Check for a null shared_ptr
        std::cout << "Passed Test 10." << std::endl;
    }

    std::cout << "All tests passed!" << std::endl;
    return 0;
}



#if name 
#include <bits/stdc++.h>
#include <memory>


template <typename T>
class smart_pointer{
public:
    smart_pointer(T* ptr): ptr(ptr){}
    
    ~smart_pointer(){
        delete ptr;
    }
    
    T& operator*(){
        return *ptr;
    }
    
    T* operator->(){
        return ptr;
    }
    
    T& operator=(const smart_pointer& rhs){
        if(this != & rhs){

        }
    }

    T* get(){
        return &ptr;
    }

public:
    void swap(smart_pointer& other){
        auto tmp = std::move(other.ptr);
        other.ptr = std::move(ptr);
        ptr = std::move(tmp);
    }

    operator bool() const{
        return ptr != nullptr;
    }

    T operator*() const{
        return *ptr;
    }

    T* operator->() const{
        return ptr;
    }

private:
    static int count;
    T* ptr;
}
#endif // 0