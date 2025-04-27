#ifndef JSON_API_HPP
#define JSON_API_HPP

#include "json_value.hpp"
#include "json_object.hpp"
#include <string>
#include <fstream>


class json {
public:
    json(const std::string& filepath);
    
    std::unique_ptr<json_value> read() const;
    void write(const json_value& j, int indent = 4) const;
    template<typename T>
    T get(const json_value& j, const std::string& key) const;
    template<typename T>
    void set(json_object& j, const std::string& key, const T& value) const;
    void remove(json_object& j, const std::string& key) const;
    bool has(const json_value& j, const std::string& key) const;
    static std::unique_ptr<json_value> parse(const std::string& input);

private:
    std::string filepath_;
};

#endif // JSON_API_HPP