#include "../include/json_string.hpp"

json_string::json_string(const std::string& value) : value_(value) {}

json_string::json_string(const json_string& other) : value_(other.value_) {}

json_string::json_string(json_string&& other) noexcept : value_(std::move(other.value_)) {}

json_string& json_string::operator=(const json_string& other) {
    if (this != &other) {
        value_ = other.value_;
    }

    return *this;
}

json_string& json_string::operator=(json_string&& other) noexcept {
    if (this != &other) {
        value_ = std::move(other.value_);
    }
    
    return *this;
}

json_string& json_string::operator=(std::unique_ptr<json_value>&& value) {
    if (!value || value->type() != json_type::string) {
        throw std::runtime_error("Cannot assign non-string value to json_string");
    }
    
    value_ = dynamic_cast<json_string&>(*value).value_;
    return *this;
}

json_type json_string::type() const { 
    return json_type::string; 
}

std::string json_string::dump(int indent, int current_indent) const {
    std::ostringstream oss;
    if (indent >= 0){ 
        oss << std::string(current_indent, ' ');
    }
    
    oss << "\"" << value_ << "\"";
    return oss.str();
}

std::unique_ptr<json_value> json_string::clone() const {
    return std::make_unique<json_string>(value_);
}

const std::string& json_string::get_value() const { 
    return value_; 
}