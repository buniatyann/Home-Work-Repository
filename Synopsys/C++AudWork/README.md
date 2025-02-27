# Custom `SharedPtr` Implementation

This repository contains a custom implementation of a **shared pointer** (`SharedPtr`), which is a part of C++'s smart pointers that automatically manage the lifetime of dynamically allocated objects. It is a part of a custom memory management utility that aims to implement shared ownership semantics with automatic reference counting.

## Overview

The `SharedPtr` class is a template-based smart pointer that provides shared ownership of an object. Multiple `SharedPtr` instances can point to the same object, and the object is automatically deleted when the last `SharedPtr` pointing to it is destroyed.

This custom implementation mimics the behavior of `std::shared_ptr` in C++ while focusing on:
- **Atomic reference counting** for thread safety.
- **Custom deleters** for flexible memory management.
- **Copy and move semantics**.
- Simplified memory management with `make_shared` utility.

### Key Features

1. **Thread-Safe Reference Counting**: The reference count is managed atomically using `std::atomic` to ensure that the object is properly cleaned up, even in multithreaded environments.
2. **Automatic Memory Management**: Objects are automatically deleted when there are no more references to them, preventing memory leaks.
3. **Custom Deleters**: Supports custom deleters for handling resource cleanup beyond just `delete`.
4. **Copy-and-Swap Idiom**: Ensures exception-safe copy assignment and maintains reference count integrity.
5. **Move Semantics**: Efficiently transfers ownership without copying resources.
6. **Helper Function `make_shared`**: A utility to create shared pointers with ease.

## Important Classes and Functions

### `SharedPtr`

This is the main class in this implementation. It represents a shared ownership pointer to an object.

#### Key Member Functions

1. **`SharedPtr(T* ptr = nullptr, D deleter = D())`**  
   Constructs a `SharedPtr` from a raw pointer `ptr` and an optional deleter.  
   - `ptr`: A raw pointer to the object to manage.
   - `deleter`: A custom deleter function or functor (defaults to `DefaultDeleter`).

2. **`SharedPtr(const SharedPtr<T>& other)`**  
   Copy constructor. Increments the reference count of the shared object.

3. **`SharedPtr(SharedPtr<T>&& other) noexcept`**  
   Move constructor. Transfers ownership from the other shared pointer.

4. **`SharedPtr<T>& operator=(SharedPtr<T> other)`**  
   Copy assignment operator using the **copy-and-swap idiom**. It ensures that the assignment is exception-safe and handles reference count adjustments properly.

5. **`T* get() const`**  
   Returns the raw pointer that the `SharedPtr` is managing.

6. **`T& operator*() const`**  
   Dereference operator to access the object the pointer is managing.

7. **`T* operator->() const`**  
   Member access operator to access members of the object managed by the `SharedPtr`.

8. **`unsigned int use_count() const`**  
   Returns the current reference count (number of `SharedPtr` objects pointing to the managed object).

9. **`void reset(T* ptr = nullptr, D deleter = D())`**  
   Resets the `SharedPtr` to manage a new object. If the current object is the last reference, it will be deleted.

10. **`void swap(SharedPtr<T>& other)`**  
   Swaps the state of two `SharedPtr` instances, i.e., swaps their underlying `SharedPtrImpl` objects.

11. **`~SharedPtr()`**  
   Destructor that decrements the reference count. If the reference count drops to zero, the managed object is deleted.

### `make_shared`

This is a utility function that creates a `SharedPtr` in a more efficient way by allocating memory for both the object and the control block in a single allocation.

#### **`make_shared<T>(Args&&... args)`**
Creates and returns a `SharedPtr` managing an object of type `T` constructed with the given arguments `args...`.

Team members:
- Buniatyan Narek
- Stepanyan Zemfira
