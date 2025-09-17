cmake_minimum_required(VERSION 3.5)

project(187_const_member_functions LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(187_const_member_functions main.cpp)


include(GNUInstallDirs)
install(TARGETS 187_const_member_functions
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
