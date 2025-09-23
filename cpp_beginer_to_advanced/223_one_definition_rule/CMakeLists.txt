cmake_minimum_required(VERSION 3.5)

project(223_one_definition_rule LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(223_one_definition_rule main.cpp)


include(GNUInstallDirs)
install(TARGETS 223_one_definition_rule
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
