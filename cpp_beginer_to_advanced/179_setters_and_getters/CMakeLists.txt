cmake_minimum_required(VERSION 3.5)

project(179_setters_and_getters LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(179_setters_and_getters main.cpp)

include(GNUInstallDirs)
install(TARGETS 179_setters_and_getters
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
