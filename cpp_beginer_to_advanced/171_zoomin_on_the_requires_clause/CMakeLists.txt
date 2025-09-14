cmake_minimum_required(VERSION 3.5)

project(171_zoomin_on_the_requires_clause LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(171_zoomin_on_the_requires_clause main.cpp)

include(GNUInstallDirs)
install(TARGETS 171_zoomin_on_the_requires_clause
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
