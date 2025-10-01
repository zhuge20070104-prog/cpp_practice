cmake_minimum_required(VERSION 3.5)

project(266_default_ordering_with_spaceship_operator LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(266_default_ordering_with_spaceship_operator main.cpp
    item.h integer.h)


include(GNUInstallDirs)
install(TARGETS 266_default_ordering_with_spaceship_operator
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
