#ifndef JSON_ARRAY_HPP
#define JSON_ARRAY_HPP

#include "json_value.hpp"
#include <vector>
#include <sstream>
#include <stdexcept>


class json_array : public json_value {
public:
    using array = std::vector<std::unique_ptr<json_value>>;

    json_array();
    json_array(const array& values);
    json_array(const json_array& other);
    json_array(json_array&& other) noexcept;
    json_array& operator=(const json_array& other);
    json_array& operator=(json_array&& other) noexcept;
    json_array& operator=(std::unique_ptr<json_value>&& value);

    json_type type() const override;
    std::string dump(int indent = -1, int current_indent = 0) const override;
    std::unique_ptr<json_value> clone() const override;

    const array& get_values() const;
    void add_value(std::unique_ptr<json_value> value);
    json_value& operator[](size_t index);
    const json_value& operator[](size_t index) const;
    void set_element(size_t index, std::unique_ptr<json_value> value);

private:
    array values_;
};

#endif // JSON_ARRAY_HPP