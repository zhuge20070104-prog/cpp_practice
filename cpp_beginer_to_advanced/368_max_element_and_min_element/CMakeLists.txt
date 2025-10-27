cmake_minimum_required(VERSION 3.5)

project(368_max_element_and_min_element LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(368_max_element_and_min_element main.cpp)


include(GNUInstallDirs)
install(TARGETS 368_max_element_and_min_element
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
