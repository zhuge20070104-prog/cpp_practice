cmake_minimum_required(VERSION 3.5)

project(279_inheriting_base_constructors LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(279_inheriting_base_constructors main.cpp
    person.cpp
    engineer.cpp)


include(GNUInstallDirs)
install(TARGETS 279_inheriting_base_constructors
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
