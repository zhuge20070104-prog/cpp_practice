cmake_minimum_required(VERSION 3.5)

project(274_closing_in_on_private_inheritance LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(274_closing_in_on_private_inheritance main.cpp
    person.cpp
    engineer.cpp
    civil_engineer.cpp)


include(GNUInstallDirs)
install(TARGETS 274_closing_in_on_private_inheritance
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
