cmake_minimum_required(VERSION 3.5)

project(278_copy_constructor_with_inheritance LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(278_copy_constructor_with_inheritance main.cpp
    person.cpp
    engineer.cpp
    civil_engineer.cpp)


include(GNUInstallDirs)
install(TARGETS 278_copy_constructor_with_inheritance
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
