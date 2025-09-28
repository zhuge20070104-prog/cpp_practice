cmake_minimum_required(VERSION 3.5)

project(241_unary_post_increment_operator LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(241_unary_post_increment_operator main.cpp
    car.cpp
    number.cpp
    point.cpp)


include(GNUInstallDirs)
install(TARGETS 241_unary_post_increment_operator
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
