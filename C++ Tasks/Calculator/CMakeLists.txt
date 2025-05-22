cmake_minimum_required(VERSION 3.10)
project(Calculator LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(${CMAKE_SOURCE_DIR}/include)

set(SOURCES
    src/ast/expression_node.cpp
    src/ast/number_node.cpp
    src/ast/operator_node.cpp
    src/ast/function_node.cpp
    src/lexer/token.cpp
    src/lexer/lexer.cpp
    src/parser/parser.cpp
    src/calculator/calculator_error.cpp
    src/calculator/calculator.cpp
    main.cpp
)

add_executable(calculator ${SOURCES})

# Ensure PIE
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fPIE")