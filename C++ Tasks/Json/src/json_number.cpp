#include "../include/json_number.hpp"

json_number::json_number(double value) : value_(value) {}

json_number::json_number(const json_number& other) : value_(other.value_) {}

json_number::json_number(json_number&& other) noexcept : value_(other.value_) {
    other.value_ = 0.0;
}

json_number& json_number::operator=(const json_number& other) {
    if (this != &other) {
        value_ = other.value_;
    }
    
    return *this;
}

json_number& json_number::operator=(json_number&& other) noexcept {
    if (this != &other) {
        value_ = other.value_;
        other.value_ = 0.0;
    }
    
    return *this;
}

json_number& json_number::operator=(std::unique_ptr<json_value>&& value) {
    if (!value || value->type() != json_type::number) {
        throw std::runtime_error("Cannot assign non-number value to json_number");
    }
    
    value_ = dynamic_cast<json_number&>(*value).value_;
    return *this;
}

json_type json_number::type() const { 
    return json_type::number; 
}

std::string json_number::dump(int indent, int current_indent) const {
    std::ostringstream oss;
    if (indent >= 0){ 
        oss << std::string(current_indent, ' ');
    }
    
    if (value_ == static_cast<int64_t>(value_)) {
        oss << static_cast<int64_t>(value_);
    } 
    else {
        oss << std::fixed;
        std::string num_str = std::to_string(value_);
        size_t dot_pos = num_str.find('.');
        if (dot_pos != std::string::npos) {
            size_t end = num_str.find_last_not_of('0');
            if (num_str[end] == '.'){ 
                --end;
            }
            
            num_str = num_str.substr(0, end + 1);
        }
        
        oss << num_str;
    }

    if (indent >= 0){ 
        oss << "\n";
    }
    
    return oss.str();
}

std::unique_ptr<json_value> json_number::clone() const {
    return std::make_unique<json_number>(value_);
}

double json_number::get_value() const { 
    return value_; 
}