#include "json_array.hpp"

json_array::json_array() = default;

json_array::json_array(const array& values) {
    for (const auto& val : values) {
        add_value(val->clone());
    }
}

json_array::json_array(const json_array& other) {
    for (const auto& val : other.values_) {
        add_value(val->clone());
    }
}

json_array::json_array(json_array&& other) noexcept : values_(std::move(other.values_)) {}

json_array& json_array::operator=(const json_array& other) {
    if (this != &other) {
        values_.clear();
        for (const auto& val : other.values_) {
            add_value(val->clone());
        }
    }
    
    return *this;
}

json_array& json_array::operator=(json_array&& other) noexcept {
    if (this != &other) {
        values_ = std::move(other.values_);
    }

    return *this;
}

json_array& json_array::operator=(std::unique_ptr<json_value>&& value) {
    if (!value || value->type() != json_type::array) {
        throw std::runtime_error("Cannot assign non-array value to json_array");
    }

    values_.clear();
    for (const auto& val : dynamic_cast<json_array&>(*value).values_) {
        add_value(val->clone());
    }

    return *this;
}

json_type json_array::type() const { 
    return json_type::array;
 }