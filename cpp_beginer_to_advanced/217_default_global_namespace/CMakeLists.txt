cmake_minimum_required(VERSION 3.5)

project(217_default_global_namespace LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(217_default_global_namespace main.cpp)


include(GNUInstallDirs)
install(TARGETS 217_default_global_namespace
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
