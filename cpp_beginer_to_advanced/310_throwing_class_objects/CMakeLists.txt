cmake_minimum_required(VERSION 3.5)

project(310_throwing_class_objects LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(310_throwing_class_objects main.cpp
)


include(GNUInstallDirs)
install(TARGETS 310_throwing_class_objects
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
