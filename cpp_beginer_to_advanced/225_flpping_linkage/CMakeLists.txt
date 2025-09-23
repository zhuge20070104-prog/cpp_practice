cmake_minimum_required(VERSION 3.5)

project(225_flpping_linkage LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(225_flpping_linkage main.cpp
    other.cpp)


include(GNUInstallDirs)
install(TARGETS 225_flpping_linkage
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
