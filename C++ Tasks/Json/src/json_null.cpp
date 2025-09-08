#include "../include/json_null.hpp"

json_null& json_null::operator=(std::unique_ptr<json_value>&& value) {
    if (!value || value->type() != json_type::null) {
        throw std::runtime_error("Cannot assign non-null value to json_null");
    }
    
    return *this;
}

json_type json_null::type() const { 
    return json_type::null; 
}

std::string json_null::dump(int indent, int current_indent) const {
    return indent >= 0 ? std::string(current_indent, ' ') + "null" : "null";
}

std::unique_ptr<json_value> json_null::clone() const {
    return std::make_unique<json_null>();
}

// json_null& json_null::operator=(std::unique_ptr<json_value>&& value) {
//     if (!value || value->type() != json_type::null) {
//         throw std::runtime_error("Cannot assign non-null value to json_null");
//     }
    
//     return *this;
// }

// json_type json_null::type() const { 
//     return json_type::null;
// }

// std::string json_null::dump(int indent, int current_indent) const {
//     std::string result = indent >= 0 ? std::string(current_indent, ' ') + "null" : "null";
//     if (indent >= 0){ 
//         result += "\n";
//     }
    
//     return result;
// }

// std::unique_ptr<json_value> json_null::clone() const {
//     return std::make_unique<json_null>();
// }