cmake_minimum_required(VERSION 3.5)

project(37_std_ios_hex LANGUAGES CXX)
add_definitions(-g)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

file(GLOB SOURCE_FILES ${CMAKE_CURRENT_SOURCE_DIR}/*.cc)
add_executable(37_std_ios_hex ${CMAKE_CURRENT_SOURCE_DIR}/main.cpp
    ${SOURCE_FILES}
)
