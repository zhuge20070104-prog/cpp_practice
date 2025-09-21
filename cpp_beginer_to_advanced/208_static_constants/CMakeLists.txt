cmake_minimum_required(VERSION 3.5)

project(208_static_constants LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(208_static_constants main.cpp)


include(GNUInstallDirs)
install(TARGETS 208_static_constants
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
