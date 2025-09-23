cmake_minimum_required(VERSION 3.5)

project(221_nested_namespaces LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(221_nested_namespaces main.cpp)


include(GNUInstallDirs)
install(TARGETS 221_nested_namespaces
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
