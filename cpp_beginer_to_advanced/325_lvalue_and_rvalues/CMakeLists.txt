cmake_minimum_required(VERSION 3.5)

project(325_lvalue_and_rvalues LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(325_lvalue_and_rvalues main.cpp)


include(GNUInstallDirs)
install(TARGETS 325_lvalue_and_rvalues
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
