cmake_minimum_required(VERSION 3.5)

project(193_initializer_list_constructors LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(193_initializer_list_constructors main.cpp)


include(GNUInstallDirs)
install(TARGETS 193_initializer_list_constructors
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
