cmake_minimum_required(VERSION 3.5)

project(282_non_polymorphic_funcs_and_specifiers LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(282_non_polymorphic_funcs_and_specifiers main.cpp
    shape.cpp
    ellipse.cpp)


include(GNUInstallDirs)
install(TARGETS 282_non_polymorphic_funcs_and_specifiers
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
