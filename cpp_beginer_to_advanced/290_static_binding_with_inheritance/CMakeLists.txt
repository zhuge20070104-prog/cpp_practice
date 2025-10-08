cmake_minimum_required(VERSION 3.5)

project(290_static_binding_with_inheritance LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(290_static_binding_with_inheritance main.cpp
    circle.cpp
    oval.cpp
    shape.cpp
)


include(GNUInstallDirs)
install(TARGETS 290_static_binding_with_inheritance
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
