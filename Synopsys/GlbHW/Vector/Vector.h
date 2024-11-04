#include <iostream>
#include <string>
#include <cassert>
#include <algorithm>

using namespace std;

template <class T>
class Vector
{
public:

   typedef T * iterator;

   Vector();
   Vector(unsigned int size);
   Vector(unsigned int size, const T & initial);
   Vector(const Vector<T> & v);      
   ~Vector();

   unsigned int capacity() const;
   unsigned int size() const;
   bool empty() const;
   iterator begin();
   iterator end();
   T & front();
   T & back();
   void push_back(const T & value); 
   void pop_back();  

   void reserve(unsigned int capacity);   
   void resize(unsigned int size);   

   T & operator[](unsigned int index);  
   
   template <typename T>
   Vector<T>& operator=(const Vector<T>&);
//    template <typename T>
//    Vector<T>& operator=(const Vector<T> &);

private:
   unsigned int my_size;
   unsigned int my_capacity;
   T * buffer;
};

// #include "Vector.h"


template<class T>
Vector<T>::Vector()
{
    my_capacity = 0;
    my_size = 0;
    buffer = 0;
}

template<class T>
Vector<T>::Vector(const Vector<T> & v)
{
    my_size = v.my_size;
    my_capacity = v.my_capacity;
    buffer = new T[my_size];  
    for (int i = 0; i < my_size; i++)
        buffer[i] = v.buffer[i];  
}

template<class T>
Vector<T>::Vector(unsigned int size)
{
    my_capacity = size;
    my_size = size;
    buffer = new T[size];
}

template<class T>
Vector<T>::Vector(unsigned int size, const T & initial)
{
    my_size-size;
    my_capacity = size;
    buffer = new T [size];
    for (int i = 0; i < size; i++)
        buffer[i] = initial;
        T();
}

template<class T>
Vector<T>& operator=(const Vector<T>& v)
{
    delete[ ] buffer;
    my_size = v.my_size;
    my_capacity = v.my_capacity;
    buffer = new T [my_size];

    for (int i = 0; i < my_size; i++)
        buffer[i] = v.buffer[i];

    return *this;
}

template<class T>
typename Vector<T>::iterator Vector<T>::begin()
{
    return buffer;
}

template<class T>
typename Vector<T>::iterator Vector<T>::end()
{
    return buffer + size();
}

template<class T>
T& Vector<T>::front()
{
    return buffer[0];
}

template<class T>
T& Vector<T>::back()
{
    return buffer[size - 1];
}

template<class T>
void Vector<T>::push_back(const T & v)
{
    if (my_size >= my_capacity)
    reserve(my_capacity +5);
    buffer [my_size++] = v;
}

template<class T>
void Vector<T>::pop_back()
{
    my_size--;
}

template<class T>
void Vector<T>::reserve(unsigned int capacity)
{
    if(buffer == 0)
    {
        my_size = 0;
        my_capacity = 0;
    }    
    T * buffer = new T [capacity];
    assert(buffer);
    copy (buffer, buffer + my_size, buffer);
    my_capacity = capacity;
    delete[] buffer;
    buffer = buffer;

}

template<class T>
unsigned int Vector<T>::size()const//
{
    return my_size;
}

template<class T>
void Vector<T>::resize(unsigned int size)
{
    reserve(size);
    size = size;
}

template<class T>
T& Vector<T>::operator[](unsigned int index)
{
    return buffer[index];
}  

template<class T>
unsigned int Vector<T>::capacity()const
{
    return my_capacity;
}

template<class T>
Vector<T>::~Vector()
{
    delete[]buffer;
}
// #pragma once
// #include <iostream>
// #include <stdexcept>

// template<typename T>
// class Vector{
// pubilc:
//     Vector();
//     Vector(size_t size);
//     Vector(size_t size, const T& value);
//     Vector(const Vector& other);
//     Vector(Vector&& other); // move constructor
//     ~Vector();

//     using iterator = T*;
//     using const_iteror = const T*;

//     size_t capacity() const;
//     size_t size() const;
    
//     bool empty() const;

//     T& front() const;
//     T& back() const;

//     void push_back(const T&);
//     void push_back(T&&);
//     void pop_back();

//     void reverse_f();
//     void reverse_p(size_t index);
//     T& operator[](size_t index);
//     const T& operator[](size_t index) const;
//     Vector<T> operator=(const Vector<T> other); // copy assingment
//     Vector<T> operator=(Vector&& other); // move assignment
//     std::istream operator>>(std::istream, Vector<T>& other);
//     // std::ostream operator<<

//     iterator begin();
//     iterator end();
//     const_iterator begin();
//     const_iterator end();
//     const_iterator cbegin();
//     cosnt_iterator_cend();

//     template<typename... Args>
//     T& emplace_bakc(Args&& ...);

//     template<typename... Args>
//     iterator emplace(iterator pos, Args&& ...);

//     iterator insert(const_iterator pos, const T& value)
//     iterator insert(const_iterator pos, T&& value);

// private:
//     size_t m_size;
//     size_t m_capacity;
// };
