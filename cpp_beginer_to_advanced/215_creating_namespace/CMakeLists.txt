cmake_minimum_required(VERSION 3.5)

project(215_creating_namespace LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(215_creating_namespace main.cpp)


include(GNUInstallDirs)
install(TARGETS 215_creating_namespace
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
