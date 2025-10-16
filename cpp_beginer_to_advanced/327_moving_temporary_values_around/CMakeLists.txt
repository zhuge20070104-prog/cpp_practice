cmake_minimum_required(VERSION 3.5)

project(327_moving_temporary_values_around LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(327_moving_temporary_values_around main.cpp)


include(GNUInstallDirs)
install(TARGETS 327_moving_temporary_values_around
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
