cmake_minimum_required(VERSION 3.5)

project(301_exceptions_in_destructor LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(301_exceptions_in_destructor main.cpp
)


include(GNUInstallDirs)
install(TARGETS 301_exceptions_in_destructor
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
