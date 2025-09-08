#ifndef JSON_VALUE_HPP
#define JSON_VALUE_HPP

#include <string>
#include <memory>

class json_value;
class json_null;
class json_boolean;
class json_number;
class json_string;
class json_array;
class json_object;

enum class json_type {
    null,
    boolean,
    number,
    string,
    array,
    object
};

class json_value {
public:
    virtual ~json_value() = default;
    virtual json_type type() const = 0;
    virtual std::string dump(int indent = -1, int current_indent = 0) const = 0;
    virtual std::unique_ptr<json_value> clone() const = 0;
    virtual json_value& operator=(std::unique_ptr<json_value>&& value) = 0;

    bool is_null() const;
    bool is_boolean() const;
    bool is_number() const;
    bool is_string() const;
    bool is_array() const;
    bool is_object() const;
};

#endif // JSON_VALUE_HPP