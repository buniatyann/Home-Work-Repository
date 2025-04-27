#ifndef JSON_NULL_HPP
#define JSON_NULL_HPP

#include "json_value.hpp"
#include <stdexcept>

class json_null : public json_value {
public:
    json_null() = default;
    json_null(const json_null& other) = default;
    json_null(json_null&& other) noexcept = default;
    json_null& operator=(const json_null& other) = default;
    json_null& operator=(json_null&& other) noexcept = default;
    json_null& operator=(std::unique_ptr<json_value>&& value) override;
    
    json_type type() const override;
    std::string dump(int indent = -1, int current_indent = 0) const override;
    std::unique_ptr<json_value> clone() const override;
};

#endif // JSON_NULL_HPP