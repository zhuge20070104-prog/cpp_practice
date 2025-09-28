cmake_minimum_required(VERSION 3.5)

project(250_subscript_operator_for_reading_and_writting LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(250_subscript_operator_for_reading_and_writting main.cpp
    car.cpp
    number.cpp
    point.cpp)


include(GNUInstallDirs)
install(TARGETS 250_subscript_operator_for_reading_and_writting
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
