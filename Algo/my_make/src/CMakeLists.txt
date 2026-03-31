add_library(my_make_lib STATIC
    cli/cli.cpp
    lexer/lexer.cpp
    parser/parser.cpp
    variables/variable_table.cpp
    rules/rule_database.cpp
    graph/graph.cpp
    executor/executor.cpp
    errors/errors.cpp
)
target_include_directories(my_make_lib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

add_executable(my_make main.cpp)
target_link_libraries(my_make PRIVATE my_make_lib)
