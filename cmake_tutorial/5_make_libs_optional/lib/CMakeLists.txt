cmake_minimum_required(VERSION 3.10.2)

project(my_math)

add_library(${PROJECT_NAME} adder.cpp)
set_target_properties(my_math PROPERTIES PUBLIC_HEADER adder.h) 
install(TARGETS ${PROJECT_NAME}  DESTINATION lib
    PUBLIC_HEADER DESTINATION include)