cmake_minimum_required(VERSION 3.10.2)

project(my_math)

add_library(${PROJECT_NAME} adder.cpp)
install(TARGETS ${PROJECT_NAME}  DESTINATION lib)
install(FILES adder.h DESTINATION include)