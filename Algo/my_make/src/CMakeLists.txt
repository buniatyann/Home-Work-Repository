add_library(my_make_lib STATIC
    # core
    modules/core/errors/errors.cpp

    # parser (lexer + parser + ast)
    modules/parser/lexer/lexer.cpp
    modules/parser/parser/parser.cpp

    # eval (variable table + expander)
    modules/eval/variable_table.cpp
    modules/eval/expander.cpp

    # engine (rules + graph + executor)
    modules/engine/rule_database/rule_database.cpp
    modules/engine/graph/graph.cpp
    modules/engine/execution/executor.cpp

    # cli
    modules/cli/cli.cpp
)
target_include_directories(my_make_lib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/modules)

add_executable(my_make app/main.cpp)
target_link_libraries(my_make PRIVATE my_make_lib)
