cmake_minimum_required(VERSION 3.5)

project(269_inheritance_and_distructors LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(269_inheritance_and_distructors main.cpp
    person.cpp
    engineer.cpp
    civil_engineer.cpp)


include(GNUInstallDirs)
install(TARGETS 269_inheritance_and_distructors
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
