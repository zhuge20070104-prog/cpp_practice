cmake_minimum_required(VERSION 3.5)

project(297_inheritance_and_polymorphism_with_static_members LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(297_inheritance_and_polymorphism_with_static_members main.cpp
    shape.cpp
    ellipse.cpp
)


include(GNUInstallDirs)
install(TARGETS 297_inheritance_and_polymorphism_with_static_members
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
