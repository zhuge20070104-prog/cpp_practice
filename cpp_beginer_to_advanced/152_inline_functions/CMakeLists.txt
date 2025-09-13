cmake_minimum_required(VERSION 3.5)

project(152_inline_functions LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(152_inline_functions main.cpp)

include(GNUInstallDirs)
install(TARGETS 152_inline_functions
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
