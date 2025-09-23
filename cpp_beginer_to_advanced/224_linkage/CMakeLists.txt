cmake_minimum_required(VERSION 3.5)

project(224_linkage LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(224_linkage main.cpp
    other.cpp)


include(GNUInstallDirs)
install(TARGETS 224_linkage
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
