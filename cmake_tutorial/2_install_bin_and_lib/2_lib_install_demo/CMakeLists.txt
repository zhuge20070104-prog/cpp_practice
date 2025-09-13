cmake_minimum_required(VERSION 3.10.2)

project(add)

add_definitions(-g)

add_executable(${PROJECT_NAME} main.cpp)

target_link_libraries(${PROJECT_NAME} my_math)