#include "String.h"

String::String(int cap)
{
    this->size = 0;
    this->capacity = cap;
    str_data = new char[capacity]{'\0'};
}

String::String(const String& other)
{
    this->str_data = new char[other.capacity];
    this->size = other.size;
    this->capacity = other.capacity;
    strcpy(str_data, other.str_data);
}

String::String(String&& other) noexcept
{
    this->capacity = other.capacity;
    this->size = other.size;
    this->str_data = other.str_data;

    other.str_data = nullptr;
    other.size = 0;
    other.capacity = 0;
}

String::String(const char* cstr)
{
    size = strlen(cstr);
    capacity = size + 1;
    str_data = new char[capacity];
    strcpy(str_data, cstr);
}

String::~String()
{
    delete[] str_data;
}

int String::size() const
{
    return this->size;
}

int String::length() const
{
    return this->size;
}

int String::capacity() const
{
    return this->capacity;
}

void String::push_back(char c)
{
    if(size + 1 >= capacity){
        _set_capacity(capacity * 2);
    }

    str_data[size] = c;
    ++size;
    str_data[size] = '\0';
}

void String::appned(const char* cstr)
{
    if(size + strlen(cstr) >= capacity){
        _set_capacity(size + strlen(cstr) + 1);
    }

    strcpy(str_data + strlen(cstr), cstr);
}

void String::append(const String& other)
{
    append(other.str_data);
}

void String::pop_back()
{
    if (size > 0) {
        str_data[--size] = '\0';
    }
}

bool String::empty()
{
    return this->size == 0;
}

void String::clear()
{
    size = 0;
    str_data[0] = '\0';
}

void String::insert_at(int index, char c)
{
    if(index > size) {
        throw std::out_of_range("Index out of range");
    }
    if(size + 1 >= capacity) {
        _set_capacity(capacity * 2);
    }
        
    for(int i = size; i > index; --i) {
        str_data[i] = str_data[i - 1];
    }

    str_data[index] = c;
    size++;
    str_data[size] = '\0';
}

bool String::operator==(const String& other)
{
    return strcmp(this->str_data, other.str_data) == 0;
}

bool String::operator!=(const String& other)
{
    return !(*this == other);
}

bool String::operator>(const String& other)
{
    return strcmp(this->str_data, other.str_data) > 0;
}

bool String::operator<=(const String& other)
{
    return !(*this > other);
}

bool String::operator<(const String& other)
{
    return strcmp(this->str_data, other.str_data) < 0;
}

bool String::operator>=(const String& other)
{
    return !(*this < other);
}

String& String::operator+(const String& other)
{
    String result;
    result.append(*this);
    result.append(other);   

    return result;
}

String &String::operator+=(const String& other)
{
    this->append(other);

    return *this;
}

String &String::operator=(const String& other)
{
    if(*this != other){
        delete[] str_data; // Clean up current memory
        size = other.size;
        capacity = other.capacity;
        str_data = new char[capacity];
        strcpy(str_data, other.str_data);
    }

    return *this;
}

String &String::operator=(String&& other) noexcept
{
    if(*this != other){
        delete[] this->str_data;
        size = other.size;
        capacity = other.capacity;
        str_data = new char[capacity];
        other.str_data = nullptr;
        other.capacity = 0;
        other.size = 0;
    }

    return *this;
}

String& String::substr(int start, int len)
{
    if (start >= size){
        throw std::out_of_range("out of range ");
    }

    len = (len < size - start) ? len : size - start;
    String result(len);
    strncpy(result.str_data, str_data + start, len);
    result.str_data[len] = '\0';
    result.size = len;

    return result;
}

char& String::operator[](int index)
{
    assert(index < size && index >= 0);
    return str_data[index];
}

void String::_set_capacity(int new_capacity)
{
    if (new_capacity <= capacity) {
            return; // No need to resize
    }
        
    char* new_buffer = new char[new_capacity];
    strcpy(new_buffer, str_data); 
    delete[] str_data;
    str_data = new_buffer;
    capacity = new_capacity;
    
}
