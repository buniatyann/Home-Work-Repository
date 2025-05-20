cmake_minimum_required(VERSION 3.14)
project(NFAEngineProject)

# C++ standard
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Include directories
include_directories(
    include
    include/ast
    include/nfa
    include/matchers
    include/grammar
    include/builder
)

# Source files
set(SOURCE_FILES
    src/ast/ast.cpp
    src/nfa/nfa_regex.cpp
    src/nfa/engine_nfa.cpp
    src/matchers/matchers.cpp
    src/matchers/match.cpp
    src/grammar/grammar.cpp
    src/builder/conversion_builder.cpp
)

# Executable (or library)
add_executable(nfa_engine ${SOURCE_FILES})
