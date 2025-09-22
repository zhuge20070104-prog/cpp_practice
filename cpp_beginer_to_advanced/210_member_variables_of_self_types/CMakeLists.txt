cmake_minimum_required(VERSION 3.5)

project(210_member_variables_of_self_types LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(210_member_variables_of_self_types main.cpp)


include(GNUInstallDirs)
install(TARGETS 210_member_variables_of_self_types
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
