#include "include/json.hpp"
#include "include/json_object.hpp"
#include "include/json_number.hpp"
#include "include/json_string.hpp"
#include <iostream>

int main() {
    try {
        json json_api("jsn.json");

        // Create JSON using set_value
        json_object j;
        j.set_value("age", std::make_unique<json_number>(25.8));
        j.set_value("name", std::make_unique<json_string>("John"));

        // Write to file
        json_api.write(j, 4);

        // Read from file
        auto data = json_api.read();
        json_object& obj = dynamic_cast<json_object&>(*data);

        // Access value using operator[]
        double age = dynamic_cast<json_number&>(obj["age"]).get_value();
        std::cout << "Age: " << age << std::endl; // Outputs: Age: 25.8

        // Modify value using set_value
        obj.set_value("age", std::make_unique<json_number>(30.5));
        json_api.write(obj, 4);

        // Check key
        if (json_api.has(obj, "age")) {
            std::cout << "Key 'age' exists" << std::endl;
        }

        // Remove key
        json_api.remove(obj, "age");
        json_api.write(obj, 4);

        // Verify removal
        if (!json_api.has(obj, "age")) {
            std::cout << "Key 'age' removed" << std::endl;
        }

        // Demonstrate copy and move
        json_object j_copy = j; // Copy constructor
        json_object j_move = std::move(j_copy); // Move constructor
        j_copy = j_move; // Copy assignment
        j_move = std::move(j_copy); // Move assignment
        std::cout << "Moved object: " << j_move.dump() << std::endl;
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }
    
    return 0;
}