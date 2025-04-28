#include "include/json_value.hpp"
#include "include/json_null.hpp"
#include "include/json_boolean.hpp"
#include "include/json_number.hpp"
#include "include/json_string.hpp"
#include "include/json_array.hpp"
#include "include/json_object.hpp"
#include "include/lexer.hpp"
#include "include/parser.hpp"
#include "include/json.hpp"
#include <iostream>
#include <fstream>

// Simple test framework
class test_suite {
public:
    void add_test(const std::string& name, bool (*test_func)()) {
        tests.push_back({name, test_func});
    }

    void run_tests() {
        size_t passed = 0;
        std::cout << "Running " << tests.size() << " tests...\n";
        for (const auto& test : tests) {
            std::cout << "Test: " << test.name << " ... ";
            try {
                bool result = test.func();
                if (result) {
                    std::cout << "PASSED\n";
                    ++passed;
                } else {
                    std::cout << "FAILED\n";
                }
            } catch (const std::exception& e) {
                std::cout << "FAILED (Exception: " << e.what() << ")\n";
            }
        }
        std::cout << "Summary: " << passed << "/" << tests.size() << " tests passed.\n";
    }

private:
    struct test_case {
        std::string name;
        bool (*func)();
    };
    std::vector<test_case> tests;
};

// Helper function to compare doubles
bool doubles_equal(double a, double b, double epsilon = 1e-6) {
    return std::abs(a - b) < epsilon;
}

// json_null test cases
bool test_json_null_create_dump() {
    json_null j;
    return j.is_null() && j.dump() == "null" && j.dump(4) == "    null";
}

bool test_json_null_clone() {
    json_null j;
    auto clone = j.clone();
    return clone->is_null() && clone->dump() == "null";
}

bool test_json_null_constructors_assignments() {
    json_null j1;
    json_null j2(j1); // Copy constructor
    json_null j3(std::move(j1)); // Move constructor
    json_null j4;
    j4 = j2; // Copy assignment
    json_null j5;
    j5 = std::move(j3); // Move assignment
    return j2.is_null() && j4.is_null() && j5.is_null();
}

// json_boolean test cases
bool test_json_boolean_create_dump() {
    json_boolean j1(true), j2(false);
    return j1.is_boolean() && j1.get_value() && j1.dump() == "true" &&
           j2.is_boolean() && !j2.get_value() && j2.dump() == "false";
}

bool test_json_boolean_clone() {
    json_boolean j(true);
    auto clone = j.clone();
    return clone->is_boolean() && dynamic_cast<json_boolean&>(*clone).get_value();
}

bool test_json_boolean_constructors_assignments() {
    json_boolean j1(true);
    json_boolean j2(j1); // Copy constructor
    json_boolean j3(std::move(j1)); // Move constructor
    json_boolean j4(false);
    j4 = j2; // Copy assignment
    json_boolean j5(false);
    j5 = std::move(j3); // Move assignment
    return j2.get_value() && j4.get_value() && j5.get_value();
}

// json_number test cases
bool test_json_number_create_dump() {
    json_number j1(42.0), j2(25.8);
    return j1.is_number() && doubles_equal(j1.get_value(), 42.0) && j1.dump() == "42" &&
           j2.is_number() && doubles_equal(j2.get_value(), 25.8) && j2.dump() == "25.8";
}

bool test_json_number_clone() {
    json_number j(25.8);
    auto clone = j.clone();
    return clone->is_number() && doubles_equal(dynamic_cast<json_number&>(*clone).get_value(), 25.8);
}

bool test_json_number_constructors_assignments() {
    json_number j1(25.8);
    json_number j2(j1); // Copy constructor
    json_number j3(std::move(j1)); // Move constructor
    json_number j4(0.0);
    j4 = j2; // Copy assignment
    json_number j5(0.0);
    j5 = std::move(j3); // Move assignment
    return doubles_equal(j2.get_value(), 25.8) &&
           doubles_equal(j4.get_value(), 25.8) &&
           doubles_equal(j5.get_value(), 25.8);
}

// json_string test cases
bool test_json_string_create_dump() {
    json_string j("hello");
    return j.is_string() && j.get_value() == "hello" && j.dump() == "\"hello\"";
}

bool test_json_string_clone() {
    json_string j("test");
    auto clone = j.clone();
    return clone->is_string() && dynamic_cast<json_string&>(*clone).get_value() == "test";
}

bool test_json_string_constructors_assignments() {
    json_string j1("test");
    json_string j2(j1); // Copy constructor
    json_string j3(std::move(j1)); // Move constructor
    json_string j4("");
    j4 = j2; // Copy assignment
    json_string j5("");
    j5 = std::move(j3); // Move assignment
    return j2.get_value() == "test" && j4.get_value() == "test" && j5.get_value() == "test";
}

// json_array test cases
bool test_json_array_create_dump() {
    json_array j;
    j.add_value(std::make_unique<json_number>(1));
    j.add_value(std::make_unique<json_string>("two"));
    std::string expected = "[1,\"two\"]";
    std::string expected_pretty = "[\n    1,\n    \"two\"\n]";
    return j.is_array() && j.get_values().size() == 2 &&
           j.dump() == expected && j.dump(4) == expected_pretty;
}

bool test_json_array_clone() {
    json_array j;
    j.add_value(std::make_unique<json_number>(1));
    auto clone = j.clone();
    return clone->is_array() && dynamic_cast<json_array&>(*clone).get_values().size() == 1 &&
           dynamic_cast<json_array&>(*clone).get_values()[0]->is_number();
}

bool test_json_array_constructors_assignments() {
    json_array j1;
    j1.add_value(std::make_unique<json_number>(1));
    json_array j2(j1); // Copy constructor
    json_array j3(std::move(j1)); // Move constructor
    json_array j4;
    j4 = j2; // Copy assignment
    json_array j5;
    j5 = std::move(j3); // Move assignment
    return j2.get_values().size() == 1 && j2[0].is_number() &&
           j4.get_values().size() == 1 && j4[0].is_number() &&
           j5.get_values().size() == 1 && j5[0].is_number();
}

bool test_json_array_operator_bracket() {
    json_array j;
    j.add_value(std::make_unique<json_number>(1));
    j.add_value(std::make_unique<json_string>("two"));
    j.set_element(0, std::make_unique<json_number>(42)); // Mutable access
    const json_array& j_const = j;
    return j[0].is_number() && doubles_equal(dynamic_cast<const json_number&>(j[0]).get_value(), 42) &&
           j_const[1].is_string() && dynamic_cast<const json_string&>(j_const[1]).get_value() == "two";
}

// json_object test cases
bool test_json_object_create_dump() {
    json_object j;
    j.set_value("age", std::make_unique<json_number>(25.8));
    std::string expected = "{\"age\":25.8}";
    std::string expected_pretty = "{\n    \"age\": 25.8\n}";
    return j.is_object() && j.get_values().size() == 1 &&
           j.dump() == expected && j.dump(4) == expected_pretty;
}

bool test_json_object_clone() {
    json_object j;
    j.set_value("age", std::make_unique<json_number>(25.8));
    auto clone = j.clone();
    return clone->is_object() && dynamic_cast<json_object&>(*clone).get_values().size() == 1 &&
           dynamic_cast<json_object&>(*clone).get_values().at("age")->is_number();
}

bool test_json_object_has_remove() {
    json_object j;
    j.set_value("age", std::make_unique<json_number>(25.8));
    bool has_age = j.has_key("age");
    j.remove_key("age");
    bool has_age_after = j.has_key("age");
    return has_age && !has_age_after;
}

bool test_json_object_constructors_assignments() {
    json_object j1;
    j1.set_value("age", std::make_unique<json_number>(25.8));
    json_object j2(j1); // Copy constructor
    json_object j3(std::move(j1)); // Move constructor
    json_object j4;
    j4 = j2; // Copy assignment
    json_object j5;
    j5 = std::move(j3); // Move assignment
    return j2.get_values().size() == 1 && j2["age"].is_number() &&
           j4.get_values().size() == 1 && j4["age"].is_number() &&
           j5.get_values().size() == 1 && j5["age"].is_number();
}

bool test_json_object_operator_bracket() {
    json_object j;
    j.set_value("age", std::make_unique<json_number>(25.8));
    j.set_value("name", std::make_unique<json_string>("John"));
    const json_object& j_const = j;
    return j["age"].is_number() && doubles_equal(dynamic_cast<const json_number&>(j["age"]).get_value(), 25.8) &&
           j_const["name"].is_string() && dynamic_cast<const json_string&>(j_const["name"]).get_value() == "John";
}

// lexer test cases
bool test_lexer_tokens() {
    std::string input = "{\"age\": 25.8, \"name\": \"John\"}";
    std::cerr << "Input: '" << input << "'\n";
    lexer lexer(input);
    std::vector<lexer::token> tokens;
    while (true) {
        auto token = lexer.next_token();
        tokens.push_back(token);
        if (token.type == lexer::token_type::end) break;
    }
    
    return tokens.size() == 10 &&
           tokens[0].type == lexer::token_type::l_brace &&
           tokens[1].type == lexer::token_type::string && tokens[1].value == "age" &&
           tokens[2].type == lexer::token_type::colon &&
           tokens[3].type == lexer::token_type::number && tokens[3].value == "25.8" &&
           tokens[4].type == lexer::token_type::comma &&
           tokens[5].type == lexer::token_type::string && tokens[5].value == "name" &&
           tokens[6].type == lexer::token_type::colon &&
           tokens[7].type == lexer::token_type::string && tokens[7].value == "John" &&
           tokens[8].type == lexer::token_type::r_brace &&
           tokens[9].type == lexer::token_type::end;
}

// parser test cases
bool test_parser_parse() {
    parser parser("{\"age\": 25.8, \"name\": \"John\"}");
    auto j = parser.parse();
    if (!j->is_object()) return false;
    const auto& obj = dynamic_cast<json_object&>(*j).get_values();
    return obj.size() == 2 &&
           obj.at("age")->is_number() &&
           doubles_equal(dynamic_cast<json_number&>(*obj.at("age")).get_value(), 25.8) &&
           obj.at("name")->is_string() &&
           dynamic_cast<json_string&>(*obj.at("name")).get_value() == "John";
}

// json test cases
bool test_json_parse() {
    auto j = json::parse("{\"age\": 25.8, \"name\": \"John\"}");
    if (!j->is_object()) return false;
    const auto& obj = dynamic_cast<json_object&>(*j).get_values();
    return obj.size() == 2 &&
           obj.at("age")->is_number() &&
           doubles_equal(dynamic_cast<json_number&>(*obj.at("age")).get_value(), 25.8) &&
           obj.at("name")->is_string() &&
           dynamic_cast<json_string&>(*obj.at("name")).get_value() == "John";
}

bool test_json_read_write() {
    json api("test.json");
    json_object j;
    j.set_value("age", std::make_unique<json_number>(25.8));
    api.write(j, 4);
    
    auto j2 = api.read();
    if (!j2->is_object()) return false;
    const auto& obj = dynamic_cast<json_object&>(*j2).get_values();
    return obj.size() == 1 &&
           obj.at("age")->is_number() &&
           doubles_equal(dynamic_cast<json_number&>(*obj.at("age")).get_value(), 25.8);
}

bool test_json_get_set() {
    json api("test.json");
    json_object j;
    api.set(j, "age", 25.8);
    api.set(j, "name", std::string("John"));
    api.set(j, "active", true);
    
    return doubles_equal(api.get<double>(j, "age"), 25.8) &&
           api.get<std::string>(j, "name") == "John" &&
           api.get<bool>(j, "active");
}

bool test_json_remove_has() {
    json api("test.json");
    json_object j;
    j.set_value("age", std::make_unique<json_number>(25.8));
    j.set_value("name", std::make_unique<json_string>("John"));
    
    bool has_age = api.has(j, "age");
    api.remove(j, "age");
    bool has_age_after = api.has(j, "age");
    bool has_name = api.has(j, "name");
    
    return has_age && !has_age_after && has_name;
}

bool test_json_error_handling() {
    json api("test.json");
    json_object j;
    j.set_value("age", std::make_unique<json_number>(25.8));
    
    bool caught = false;
    try {
        api.get<double>(j, "missing");
    } catch (const std::runtime_error&) {
        caught = true;
    }
    
    json_number not_obj(42);
    bool caught2 = false;
    try {
        api.get<double>(not_obj, "key");
    } catch (const std::runtime_error&) {
        caught2 = true;
    }
    
    return caught && caught2;
}

// Main function
int main() {
    test_suite suite;
    
    // json_null tests
    suite.add_test("json_null Create/Dump", test_json_null_create_dump);
    suite.add_test("json_null Clone", test_json_null_clone);
    suite.add_test("json_null Constructors/Assignments", test_json_null_constructors_assignments);
    
    // json_boolean tests
    suite.add_test("json_boolean Create/Dump", test_json_boolean_create_dump);
    suite.add_test("json_boolean Clone", test_json_boolean_clone);
    suite.add_test("json_boolean Constructors/Assignments", test_json_boolean_constructors_assignments);
    
    // json_number tests
    suite.add_test("json_number Create/Dump", test_json_number_create_dump);
    suite.add_test("json_number Clone", test_json_number_clone);
    suite.add_test("json_number Constructors/Assignments", test_json_number_constructors_assignments);
    
    // json_string tests
    suite.add_test("json_string Create/Dump", test_json_string_create_dump);
    suite.add_test("json_string Clone", test_json_string_clone);
    suite.add_test("json_string Constructors/Assignments", test_json_string_constructors_assignments);
    
    // json_array tests
    suite.add_test("json_array Create/Dump", test_json_array_create_dump);
    suite.add_test("json_array Clone", test_json_array_clone);
    suite.add_test("json_array Constructors/Assignments", test_json_array_constructors_assignments);
    suite.add_test("json_array Operator[]", test_json_array_operator_bracket);
    
    // json_object tests
    suite.add_test("json_object Create/Dump", test_json_object_create_dump);
    suite.add_test("json_object Clone", test_json_object_clone);
    suite.add_test("json_object Has/Remove", test_json_object_has_remove);
    suite.add_test("json_object Constructors/Assignments", test_json_object_constructors_assignments);
    suite.add_test("json_object Operator[]", test_json_object_operator_bracket);
    
    // lexer tests
    suite.add_test("lexer Tokens", test_lexer_tokens);
    
    // parser tests
    suite.add_test("parser Parse", test_parser_parse);
    
    // json tests
    suite.add_test("json Parse", test_json_parse);
    suite.add_test("json Read/Write", test_json_read_write);
    suite.add_test("json Get/Set", test_json_get_set);
    suite.add_test("json Remove/Has", test_json_remove_has);
    suite.add_test("json Error Handling", test_json_error_handling);
    
    suite.run_tests();
    return 0;
}