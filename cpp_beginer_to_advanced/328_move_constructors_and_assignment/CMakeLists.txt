cmake_minimum_required(VERSION 3.5)

project(328_move_constructors_and_assignment LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(328_move_constructors_and_assignment main.cpp)


include(GNUInstallDirs)
install(TARGETS 328_move_constructors_and_assignment
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
