cmake_minimum_required(VERSION 3.5)

project(53_initializer_list LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(53_initializer_list main.cpp)

include(GNUInstallDirs)
install(TARGETS 53_initializer_list
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
