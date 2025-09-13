cmake_minimum_required(VERSION 3.5)

project(151_static_variables LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(151_static_variables main.cpp)

include(GNUInstallDirs)
install(TARGETS 151_static_variables
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
