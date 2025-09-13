cmake_minimum_required(VERSION 3.10.2)

project(Trim)

add_definitions(-g)

add_executable(${PROJECT_NAME} main.cpp)

install(TARGETS ${PROJECT_NAME} DESTINATION bin)