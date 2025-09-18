cmake_minimum_required(VERSION 3.5)

project(194_aggregated_initialization LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(194_aggregated_initialization main.cpp)


include(GNUInstallDirs)
install(TARGETS 194_aggregated_initialization
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
