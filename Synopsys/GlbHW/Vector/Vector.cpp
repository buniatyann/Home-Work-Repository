// #include "Vector.h"


// template<class T>
// Vector<T>::Vector()
// {
//     my_capacity = 0;
//     my_size = 0;
//     buffer = 0;
// }

// template<class T>
// Vector<T>::Vector(const Vector<T> & v)
// {
//     my_size = v.my_size;
//     my_capacity = v.my_capacity;
//     buffer = new T[my_size];  
//     for (int i = 0; i < my_size; i++)
//         buffer[i] = v.buffer[i];  
// }

// template<class T>
// Vector<T>::Vector(unsigned int size)
// {
//     my_capacity = size;
//     my_size = size;
//     buffer = new T[size];
// }

// template<class T>
// Vector<T>::Vector(unsigned int size, const T & initial)
// {
//     my_size-size;
//     my_capacity = size;
//     buffer = new T [size];
//     for (int i = 0; i < size; i++)
//         buffer[i] = initial;
//         T();
// }

// template<class T>
// Vector<T>& Vector<T>::operator=(const Vector<T> & v)
// {
//     delete[ ] buffer;
//     my_size = v.my_size;
//     my_capacity = v.my_capacity;
//     buffer = new T [my_size];
//     for (int i = 0; i < my_size; i++)
//         buffer[i] = v.buffer[i];
//     return *this;
// }

// template<class T>
// typename Vector<T>::iterator Vector<T>::begin()
// {
//     return buffer;
// }

// template<class T>
// typename Vector<T>::iterator Vector<T>::end()
// {
//     return buffer + size();
// }

// template<class T>
// T& Vector<T>::Vector<T>::front()
// {
//     return buffer[0];
// }

// template<class T>
// T& Vector<T>::Vector<T>::back()
// {
//     return buffer[size - 1];
// }

// template<class T>
// void Vector<T>::push_back(const T & v)
// {
//     if (my_size >= my_capacity)
//     reserve(my_capacity +5);
//     buffer [my_size++] = v;
// }

// template<class T>
// void Vector<T>::pop_back()
// {
//     my_size--;
// }

// template<class T>
// void Vector<T>::reserve(unsigned int capacity)
// {
//     if(buffer == 0)
//     {
//         my_size = 0;
//         my_capacity = 0;
//     }    
//     T * buffer = new T [capacity];
//     assert(buffer);
//     copy (buffer, buffer + my_size, buffer);
//     my_capacity = capacity;
//     delete[] buffer;
//     buffer = buffer;

// }

// template<class T>
// unsigned int Vector<T>::size()const//
// {
//     return my_size;
// }

// template<class T>
// void Vector<T>::resize(unsigned int size)
// {
//     reserve(size);
//     size = size;
// }

// template<class T>
// T& Vector<T>::operator[](unsigned int index)
// {
//     return buffer[index];
// }  

// template<class T>
// unsigned int Vector<T>::capacity()const
// {
//     return my_capacity;
// }

// template<class T>
// Vector<T>::~Vector()
// {
//     delete[]buffer;
// }