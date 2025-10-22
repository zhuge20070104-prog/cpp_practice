cmake_minimum_required(VERSION 3.5)

project(355_sequence_container_list LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(355_sequence_container_list main.cpp)


include(GNUInstallDirs)
install(TARGETS 355_sequence_container_list
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
