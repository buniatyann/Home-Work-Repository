#ifndef JSON_STRING_HPP
#define JSON_STRING_HPP

#include "json_value.hpp"
#include <string>
#include <sstream>

class json_string : public json_value {
public:
    json_string(const std::string& value);
    json_string(const json_string& other);
    json_string(json_string&& other) noexcept;
    json_string& operator=(const json_string& other);
    json_string& operator=(json_string&& other) noexcept;
    json_string& operator=(std::unique_ptr<json_value>&& value) override;
    
    json_type type() const override;
    std::string dump(int indent = -1, int current_indent = 0) const override;
    std::unique_ptr<json_value> clone() const override;
    const std::string& get_value() const;

private:
    std::string value_;
};

#endif // JSON_STRING_HPP