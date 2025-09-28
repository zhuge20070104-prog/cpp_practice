cmake_minimum_required(VERSION 3.5)

project(240_unary_prefix_increment_operator_as_non_members LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(240_unary_prefix_increment_operator_as_non_members main.cpp
    car.cpp
    number.cpp
    point.cpp)


include(GNUInstallDirs)
install(TARGETS 240_unary_prefix_increment_operator_as_non_members
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
