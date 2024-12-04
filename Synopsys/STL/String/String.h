#ifndef STRING_H
#define STRING_H

#include <iostream>
#include <cstdlib>
#include <cstring>
#include <exception>
#include <cassert>

class String{
public:
    String();
    String(int);
    String(const String&);
    String(String&&) noexcept;
    String(const char*);
    ~String();

    int size() const;
    int length() const;
    int capacity() const;

    void push_back(char);
    void appned(const char*);
    void append(const String&);
    void pop_back();
    bool empty();
    void clear();
    void insert_at(int, char);
    //void reserve(int);

    friend std::ostream& operator<<(std::ostream& out, const String&);
    friend std::istream& operator>>(std::istream& in, const String&);

    bool operator==(const String&);
    bool operator!=(const String&);
    bool operator>(const String&);
    bool operator<=(const String&);
    bool operator<(const String&);
    bool operator>=(const String&);

    String& operator+(const String&);
    String& operator+=(const String&);
    String& operator=(const String&);
    String& operator=(String&&) noexcept;
    String& substr(int, int);
    
    char& operator[](int);
    const char* c_str();

private:
    char* str_data;
    int size;
    int m_capacity;

private:
    void _set_capacity(int);
};


#endif // STRING_H