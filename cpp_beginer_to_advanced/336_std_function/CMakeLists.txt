cmake_minimum_required(VERSION 3.5)

project(336_std_function LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(336_std_function main.cpp)


include(GNUInstallDirs)
install(TARGETS 336_std_function
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
