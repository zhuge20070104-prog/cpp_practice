cmake_minimum_required(VERSION 3.5)

project(153_recursive_function LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(153_recursive_function main.cpp)

include(GNUInstallDirs)
install(TARGETS 153_recursive_function
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
