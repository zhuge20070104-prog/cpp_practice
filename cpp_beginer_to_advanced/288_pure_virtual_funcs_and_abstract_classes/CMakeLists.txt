cmake_minimum_required(VERSION 3.5)

project(288_pure_virtual_funcs_and_abstract_classes LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(288_pure_virtual_funcs_and_abstract_classes main.cpp
    shape.cpp
    rectangle.cpp
    circle.cpp
)


include(GNUInstallDirs)
install(TARGETS 288_pure_virtual_funcs_and_abstract_classes
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
