#ifndef JSON_BOOL_HPP
#define JSON_BOOL_HPP

#include "json_value.hpp"
#include <stdexcept>

class json_boolean : public json_value {
public:
    json_boolean(bool value);
    json_boolean(const json_boolean& other);
    json_boolean(json_boolean&& other) noexcept;
    json_boolean& operator=(const json_boolean& other);
    json_boolean& operator=(json_boolean&& other) noexcept;
    json_boolean& operator=(std::unique_ptr<json_value>&& value) override;
    
    json_type type() const override;
    std::string dump(int indent = -1, int current_indent = 0) const override;
    std::unique_ptr<json_value> clone() const override;
    bool get_value() const;

private:
    bool value_;
};
#endif // JSON_BOOL_HPP