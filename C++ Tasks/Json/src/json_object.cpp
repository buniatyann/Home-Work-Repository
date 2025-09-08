#include "../include/json_object.hpp"

json_object::json_object() = default;

json_object::json_object(const object& values) {
    for (const auto& [key, val] : values) {
        set_value(key, val->clone());
    }
}

json_object::json_object(const json_object& other) {
    for (const auto& [key, val] : other.values_) {
        set_value(key, val->clone());
    }
}

json_object::json_object(json_object&& other) noexcept : values_(std::move(other.values_)) {}

json_object& json_object::operator=(const json_object& other) {
    if (this != &other) {
        values_.clear();
        for (const auto& [key, val] : other.values_) {
            set_value(key, val->clone());
        }
    }
    
    return *this;
}

json_object& json_object::operator=(json_object&& other) noexcept {
    if (this != &other) {
        values_ = std::move(other.values_);
    }
    
    return *this;
}

json_object& json_object::operator=(std::unique_ptr<json_value>&& value) {
    if (!value || value->type() != json_type::object) {
        throw std::runtime_error("Cannot assign non-object value to json_object");
    }
    
    values_.clear();
    for (const auto& [key, val] : dynamic_cast<json_object&>(*value).values_) {
        set_value(key, val->clone());
    }
    
    return *this;
}

json_type json_object::type() const { return json_type::object; }

std::string json_object::dump(int indent, int current_indent) const {
    std::ostringstream oss;
    if (indent >= 0){ 
        oss << std::string(current_indent, ' ');
    }
    
    oss << "{";
    if (indent >= 0 && !values_.empty()){ 
        oss << "\n";
    }
    
    size_t i = 0;
    for (const auto& [key, value] : values_) {
        if (indent >= 0) {
            oss << std::string(current_indent + indent, ' ');
        }
        
        oss << "\"" << key << "\":";
        if (indent >= 0){ 
            oss << " ";
        }
        
        oss << value->dump(indent, indent >= 0 ? current_indent + indent : 0);
        if (i++ < values_.size() - 1){ 
            oss << ",";
        }
        
        if (indent >= 0){ 
            oss << "\n";
        }
    }
    
    if (indent >= 0 && !values_.empty()){ 
        oss << std::string(current_indent, ' ');
    }
    
    oss << "}";
    if (indent >= 0){ 
        oss << "\n";
    }
    
    return oss.str();
}

std::unique_ptr<json_value> json_object::clone() const {
    return std::make_unique<json_object>(values_);
}

const json_object::object& json_object::get_values() const { return values_; }

void json_object::set_value(const std::string& key, std::unique_ptr<json_value> value) {
    values_[key] = std::move(value);
}

bool json_object::has_key(const std::string& key) const {
    return values_.find(key) != values_.end();
}

void json_object::remove_key(const std::string& key) {
    values_.erase(key);
}

json_value& json_object::operator[](const std::string& key) {
    auto it = values_.find(key);
    if (it == values_.end()) {
        values_[key] = std::make_unique<json_null>();
    }
 
    return *values_[key];
}

const json_value& json_object::operator[](const std::string& key) const {
    auto it = values_.find(key);
    if (it == values_.end()) {
        throw std::out_of_range("Key not found: " + key);
    }
 
    return *it->second;
}

// json_object::json_object() = default;

// json_object::json_object(const object& values) {
//     for (const auto& [key, val] : values) {
//         set_value(key, val->clone());
//     }
// }

// json_object::json_object(const json_object& other) {
//     for (const auto& [key, val] : other.values_) {
//         set_value(key, val->clone());
//     }
// }

// json_object::json_object(json_object&& other) noexcept : values_(std::move(other.values_)) {}

// json_object& json_object::operator=(const json_object& other) {
//     if (this != &other) {
//         values_.clear();
//         for (const auto& [key, val] : other.values_) {
//             set_value(key, val->clone());
//         }
//     }
    
//     return *this;
// }

// json_object& json_object::operator=(json_object&& other) noexcept {
//     if (this != &other) {
//         values_ = std::move(other.values_);
//     }
    
//     return *this;
// }

// json_object& json_object::operator=(std::unique_ptr<json_value>&& value) {
//     if (!value || value->type() != json_type::object) {
//         throw std::runtime_error("Cannot assign non-object value to json_object");
//     }
    
//     values_.clear();
//     for (const auto& [key, val] : dynamic_cast<json_object&>(*value).values_) {
//         set_value(key, val->clone());
//     }
    
//     return *this;
// }

// json_type json_object::type() const { 
//     return json_type::object; 
// }

// std::string json_object::dump(int indent, int current_indent) const {
//     std::ostringstream oss;
//     if (indent >= 0){ 
//         oss << std::string(current_indent, ' ');
//     }
    
//     oss << "{";
//     if (indent >= 0 && !values_.empty()){ 
//         oss << "\n";
//     }
    
//     size_t i = 0;
//     for (const auto& [key, value] : values_) {
//         if (indent >= 0){ 
//             oss << std::string(current_indent + indent, ' ');
//         }
        
//         oss << "\"" << key << "\":";
//         if (indent >= 0){ 
//             oss << " ";
//         }
        
//         oss << value->dump(indent, indent >= 0 ? current_indent + indent : 0);
//         if (i++ < values_.size() - 1){ 
//             oss << ",";
//         }
        
//         if (indent >= 0){ 
//             oss << "\n";
//         }
//     }
    
//     if (indent >= 0 && !values_.empty()){ 
//         oss << std::string(current_indent, ' ');
//     }
    
//     oss << "}";
//     if (indent >= 0){ 
//         oss << "\n";
//     }
    
//     return oss.str();
// }

// std::unique_ptr<json_value> json_object::clone() const {
//     return std::make_unique<json_object>(values_);
// }

// const json_object::object& json_object::get_values() const { return values_; }

// void json_object::set_value(const std::string& key, std::unique_ptr<json_value> value) {
//     values_[key] = std::move(value);
// }

// bool json_object::has_key(const std::string& key) const {
//     return values_.find(key) != values_.end();
// }

// void json_object::remove_key(const std::string& key) {
//     values_.erase(key);
// }

// json_value& json_object::operator[](const std::string& key) {
//     auto it = values_.find(key);
//     if (it == values_.end()) {
//         values_[key] = std::make_unique<json_null>();
//     }
    
//     return *values_[key];
// }

// const json_value& json_object::operator[](const std::string& key) const {
//     auto it = values_.find(key);
//     if (it == values_.end()) {
//         throw std::out_of_range("Key not found: " + key);
//     }
    
//     return *it->second;
// }

// json_object::json_object() = default;

// json_object::json_object(const object& values) {
//     for (const auto& [key, val] : values) {
//         set_value(key, val->clone());
//     }
// }

// json_object::json_object(const json_object& other) {
//     for (const auto& [key, val] : other.values_) {
//         set_value(key, val->clone());
//     }
// }

// json_object::json_object(json_object&& other) noexcept : values_(std::move(other.values_)) {}

// json_object& json_object::operator=(const json_object& other) {
//     if (this != &other) {
//         values_.clear();
//         for (const auto& [key, val] : other.values_) {
//             set_value(key, val->clone());
//         }
//     }

//     return *this;
// }

// json_object& json_object::operator=(json_object&& other) noexcept {
//     if (this != &other) {
//         values_ = std::move(other.values_);
//     }

//     return *this;
// }

// json_object& json_object::operator=(std::unique_ptr<json_value>&& value) {
//     if (!value || value->type() != json_type::object) {
//         throw std::runtime_error("Cannot assign non-object value to json_object");
//     }
    
//     values_.clear();
//     for (const auto& [key, val] : dynamic_cast<json_object&>(*value).values_) {
//         set_value(key, val->clone());
//     }
    
//     return *this;
// }

// json_type json_object::type() const { 
//     return json_type::object;
// }

// std::string json_object::dump(int indent, int current_indent) const {
//     std::ostringstream oss;
//     if (indent >= 0){ 
//         oss << std::string(current_indent, ' ');
//     }
    
//     oss << "{";
//     if (indent >= 0){ 
//         oss << "\n";
//     }
    
//     size_t i = 0;
//     for (const auto& [key, value] : values_) {
//         if (indent >= 0){ 
//             oss << std::string(current_indent + indent, ' ');
//         }
        
//         oss << "\"" << key << "\":";
//         if (indent >= 0){ 
//             oss << " ";
//         }
        
//         oss << value->dump(indent, indent >= 0 ? current_indent + indent : 0);
//         if (i++ < values_.size() - 1){ 
//             oss << ",";
//         }
//         if (indent >= 0){ 
//             oss << "\n";
//         }
//     }

//     if (indent >= 0){ 
//         oss << std::string(current_indent, ' ');
//     }
    
//     oss << "}";
//     return oss.str();
// }

// std::unique_ptr<json_value> json_object::clone() const {
//     return std::make_unique<json_object>(values_);
// }

// const json_object::object& json_object::get_values() const { return values_; }

// void json_object::set_value(const std::string& key, std::unique_ptr<json_value> value) {
//     values_[key] = std::move(value);
// }

// bool json_object::has_key(const std::string& key) const {
//     return values_.find(key) != values_.end();
// }

// void json_object::remove_key(const std::string& key) {
//     values_.erase(key);
// }

// json_value& json_object::operator[](const std::string& key) {
//     auto it = values_.find(key);
//     if (it == values_.end()) {
//         values_[key] = std::make_unique<json_null>();
//     }

//     return *values_[key];
// }

// const json_value& json_object::operator[](const std::string& key) const {
//     auto it = values_.find(key);
//     if (it == values_.end()) {
//         throw std::out_of_range("Key not found: " + key);
//     }
    
//     return *it->second;
// }