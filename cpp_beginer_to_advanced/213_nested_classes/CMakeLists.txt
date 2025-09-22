cmake_minimum_required(VERSION 3.5)

project(213_nested_classes LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(213_nested_classes main.cpp)


include(GNUInstallDirs)
install(TARGETS 213_nested_classes
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
