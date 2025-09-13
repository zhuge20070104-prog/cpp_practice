cmake_minimum_required(VERSION 3.5)

project(31_q31_includes LANGUAGES CXX)
add_definitions(-g)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

file(GLOB SOURCE_FILES ${CMAKE_CURRENT_SOURCE_DIR}/*.cc)
add_executable(31_q31_includes ${CMAKE_CURRENT_SOURCE_DIR}/main.cpp
    ${SOURCE_FILES}
)
