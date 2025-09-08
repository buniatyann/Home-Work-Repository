#ifndef JSON_NUMBER_HPP
#define JSON_NUMBER_HPP

#include "json_value.hpp"
#include <sstream>
#include <iomanip>

class json_number : public json_value {
public:
    json_number(double value);
    json_number(const json_number& other);
    json_number(json_number&& other) noexcept;
    json_number& operator=(const json_number& other);
    json_number& operator=(json_number&& other) noexcept;
    json_number& operator=(std::unique_ptr<json_value>&& value) override;
    
    json_type type() const override;
    std::string dump(int indent = -1, int current_indent = 0) const override;
    std::unique_ptr<json_value> clone() const override;
    double get_value() const;

private:
    double value_;
};

#endif // JSON_NUMBER_HPP