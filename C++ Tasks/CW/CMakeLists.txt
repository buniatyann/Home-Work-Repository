cmake_minimum_required(VERSION 3.10)

project(GraphCourseWork LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

find_package(nlohmann_json CONFIG REQUIRED)

add_executable(graph_program main.cpp Graph.cpp)

target_link_libraries(graph_program PRIVATE nlohmann_json::nlohmann_json)

install(TARGETS graph_program DESTINATION bin)
