cmake_minimum_required(VERSION 3.5)

project(13_q13_vector_deque_and_set LANGUAGES CXX)
add_definitions(-g)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

file(GLOB SOURCE_FILES ${CMAKE_CURRENT_SOURCE_DIR}/*.cc)
add_executable(13_q13_vector_deque_and_set ${CMAKE_CURRENT_SOURCE_DIR}/main.cpp
    ${SOURCE_FILES}
)
