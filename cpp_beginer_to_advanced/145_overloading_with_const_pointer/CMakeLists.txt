cmake_minimum_required(VERSION 3.5)

project(145_overloading_with_const_pointer LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(145_overloading_with_const_pointer main.cpp)

include(GNUInstallDirs)
install(TARGETS 145_overloading_with_const_pointer
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
