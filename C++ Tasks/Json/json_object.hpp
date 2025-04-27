#ifndef JSON_OBJECT_HPP
#define JSON_OBJECT_HPP

#include "json_value.hpp"
#include "json_null.hpp"
#include <unordered_map>
#include <sstream>

class json_object : public json_value {
public:
    using object = std::unordered_map<std::string, std::unique_ptr<json_value>>;
    
    json_object();
    json_object(const object& values);
    json_object(const json_object& other);
    json_object(json_object&& other) noexcept;
    json_object& operator=(const json_object& other);
    json_object& operator=(json_object&& other) noexcept;
    json_object& operator=(std::unique_ptr<json_value>&& value) override;
    
    json_type type() const override;
    std::string dump(int indent = -1, int current_indent = 0) const override;
    std::unique_ptr<json_value> clone() const override;
    const object& get_values() const;
    void set_value(const std::string& key, std::unique_ptr<json_value> value);
    bool has_key(const std::string& key) const;
    void remove_key(const std::string& key);
    json_value& operator[](const std::string& key);
    const json_value& operator[](const std::string& key) const;

private:
    object values_;
};

#endif // JSON_OBJECT_HPP