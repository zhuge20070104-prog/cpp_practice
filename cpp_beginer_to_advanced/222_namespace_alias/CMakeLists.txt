cmake_minimum_required(VERSION 3.5)

project(222_namespace_alias LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(222_namespace_alias main.cpp)


include(GNUInstallDirs)
install(TARGETS 222_namespace_alias
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
