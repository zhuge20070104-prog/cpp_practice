cmake_minimum_required(VERSION 3.5)

project(373_range_algorithms LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(373_range_algorithms main.cpp)


include(GNUInstallDirs)
install(TARGETS 373_range_algorithms
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
