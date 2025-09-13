cmake_minimum_required(VERSION 3.5)

project(138_option_output_from_func LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(138_option_output_from_func main.cpp)

include(GNUInstallDirs)
install(TARGETS 138_option_output_from_func
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
