cmake_minimum_required(VERSION 3.5)

project(268_custom_spaceship_operator_for_ordering LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(268_custom_spaceship_operator_for_ordering main.cpp
    point.cpp)


include(GNUInstallDirs)
install(TARGETS 268_custom_spaceship_operator_for_ordering
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
