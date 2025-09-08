#include "../include/json.hpp"
#include "../include/parser.hpp"
#include "../include/json_number.hpp"
#include "../include/json_string.hpp"
#include "../include/json_boolean.hpp"

json::json(const std::string& filepath) : filepath_(filepath) {}

std::unique_ptr<json_value> json::parse(const std::string& input) {
    parser parser(input);
    return parser.parse();
}

std::unique_ptr<json_value> json::read() const {
    std::ifstream file(filepath_);
    if (!file.is_open()) {
        throw std::runtime_error("Cannot open file: " + filepath_);
    }
    
    std::string content((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
    return parse(content);
}

void json::write(const json_value& j, int indent) const {
    std::ofstream file(filepath_);
    if (!file.is_open()) {
        throw std::runtime_error("Cannot write to file: " + filepath_);
    }
    
    file << j.dump(indent);
}

void json::remove(json_object& j, const std::string& key) const {
    j.remove_key(key);
}

bool json::has(const json_value& j, const std::string& key) const {
    if (!j.is_object()){ 
        return false;
    }
    
    return dynamic_cast<const json_object&>(j).has_key(key);
}

template<>
double json::get<double>(const json_value& j, const std::string& key) const {
    if (!j.is_object()){ 
        throw std::runtime_error("JSON value is not an object");
    }
    
    const auto& obj = dynamic_cast<const json_object&>(j).get_values();
    auto it = obj.find(key);
    if (it == obj.end()){ 
        throw std::runtime_error("Key not found: " + key);
    }
    if (!it->second->is_number()){
        throw std::runtime_error("Value is not a number");
    }
    
    return dynamic_cast<const json_number&>(*it->second).get_value();
}

template<>
std::string json::get<std::string>(const json_value& j, const std::string& key) const {
    if (!j.is_object()){
        throw std::runtime_error("JSON value is not an object");
    }
    
    const auto& obj = dynamic_cast<const json_object&>(j).get_values();
    auto it = obj.find(key);
    if (it == obj.end()){ 
        throw std::runtime_error("Key not found: " + key);
    }
    if (!it->second->is_string()){ 
        throw std::runtime_error("Value is not a string");
    }
    
    return dynamic_cast<const json_string&>(*it->second).get_value();
}

template<>
bool json::get<bool>(const json_value& j, const std::string& key) const {
    if (!j.is_object()){ 
        throw std::runtime_error("JSON value is not an object");
    }
    
    const auto& obj = dynamic_cast<const json_object&>(j).get_values();
    auto it = obj.find(key);
    if (it == obj.end()){ 
        throw std::runtime_error("Key not found: " + key);
    }
    if (!it->second->is_boolean()){ 
        throw std::runtime_error("Value is not a boolean");
    }
    
    return dynamic_cast<const json_boolean&>(*it->second).get_value();
}

template<>
void json::set<double>(json_object& j, const std::string& key, const double& value) const {
    j.set_value(key, std::make_unique<json_number>(value));
}

template<>
void json::set<std::string>(json_object& j, const std::string& key, const std::string& value) const {
    j.set_value(key, std::make_unique<json_string>(value));
}

template<>
void json::set<bool>(json_object& j, const std::string& key, const bool& value) const {
    j.set_value(key, std::make_unique<json_boolean>(value));
}