cmake_minimum_required(VERSION 3.5)

project(198_initlizer_list_for_constructors LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(198_initlizer_list_for_constructors main.cpp)


include(GNUInstallDirs)
install(TARGETS 198_initlizer_list_for_constructors
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
