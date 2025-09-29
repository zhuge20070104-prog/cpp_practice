cmake_minimum_required(VERSION 3.5)

project(260_zoomin_on_partial_ordering LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(260_zoomin_on_partial_ordering main.cpp)


include(GNUInstallDirs)
install(TARGETS 260_zoomin_on_partial_ordering
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
