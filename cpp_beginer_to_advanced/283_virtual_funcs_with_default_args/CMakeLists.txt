cmake_minimum_required(VERSION 3.5)

project(283_virtual_funcs_with_default_args LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(283_virtual_funcs_with_default_args main.cpp)


include(GNUInstallDirs)
install(TARGETS 283_virtual_funcs_with_default_args
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
