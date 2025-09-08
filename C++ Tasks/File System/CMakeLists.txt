cmake_minimum_required(VERSION 3.10)

# Project name
project(FileSystem)

# C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Compiler warnings and optimization
add_compile_options(-Wall -Wextra -O2)

# Include directories
include_directories(include)

# Source files
set(SOURCES
    src/FileSystem.cpp
    main.cpp
)

# Create executable
add_executable(FileSystemApp ${SOURCES})
