cmake_minimum_required(VERSION 3.5)

project(201_copy_constructors LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(201_copy_constructors main.cpp)


include(GNUInstallDirs)
install(TARGETS 201_copy_constructors
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
