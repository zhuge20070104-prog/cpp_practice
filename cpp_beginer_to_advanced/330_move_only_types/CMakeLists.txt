cmake_minimum_required(VERSION 3.5)

project(330_move_only_types LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(330_move_only_types main.cpp)


include(GNUInstallDirs)
install(TARGETS 330_move_only_types
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
