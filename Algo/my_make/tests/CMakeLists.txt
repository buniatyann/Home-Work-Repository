find_package(GTest REQUIRED)
include(GoogleTest)

add_executable(my_make_tests
    test_lexer.cpp
    test_parser.cpp
    test_graph.cpp
    test_executor.cpp
    test_variable_table.cpp
    test_expander.cpp
)
target_link_libraries(my_make_tests PRIVATE my_make_lib GTest::gtest GTest::gtest_main)

gtest_discover_tests(my_make_tests)
