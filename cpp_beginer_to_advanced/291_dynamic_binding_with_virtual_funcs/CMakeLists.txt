cmake_minimum_required(VERSION 3.5)

project(291_dynamic_binding_with_virtual_funcs LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(291_dynamic_binding_with_virtual_funcs main.cpp
    circle.cpp
    oval.cpp
    shape.cpp
)


include(GNUInstallDirs)
install(TARGETS 291_dynamic_binding_with_virtual_funcs
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
