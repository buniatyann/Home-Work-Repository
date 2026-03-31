include(FetchContent)
FetchContent_Declare(
    googletest
    GIT_REPOSITORY https://github.com/google/googletest.git
    GIT_TAG v1.14.0
)
FetchContent_MakeAvailable(googletest)

enable_testing()

add_executable(my_make_tests
    test_lexer.cpp
    test_parser.cpp
    test_variable_table.cpp
    test_graph.cpp
    test_executor.cpp
)
target_link_libraries(my_make_tests PRIVATE my_make_lib GTest::gtest_main)
include(GoogleTest)
gtest_discover_tests(my_make_tests)
