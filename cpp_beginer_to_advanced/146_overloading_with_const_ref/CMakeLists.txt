cmake_minimum_required(VERSION 3.5)

project(146_overloading_with_const_ref LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(146_overloading_with_const_ref main.cpp)

include(GNUInstallDirs)
install(TARGETS 146_overloading_with_const_ref
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
