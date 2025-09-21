cmake_minimum_required(VERSION 3.5)

project(203_move_constructors LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(203_move_constructors main.cpp)


include(GNUInstallDirs)
install(TARGETS 203_move_constructors
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
