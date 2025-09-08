#include "../include/json_value.hpp"

bool json_value::is_null() const { 
    return type() == json_type::null; 
}

bool json_value::is_boolean() const { 
    return type() == json_type::boolean; 
}

bool json_value::is_number() const { 
    return type() == json_type::number; 
}

bool json_value::is_string() const { 
    return type() == json_type::string;
}

bool json_value::is_array() const { 
    return type() == json_type::array; 
}

bool json_value::is_object() const { 
    return type() == json_type::object;
}