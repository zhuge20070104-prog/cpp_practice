cmake_minimum_required(VERSION 3.5)

project(254_other_arithmetic_operators LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(254_other_arithmetic_operators main.cpp
    car.cpp
    number.cpp
    point.cpp)


include(GNUInstallDirs)
install(TARGETS 254_other_arithmetic_operators
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
