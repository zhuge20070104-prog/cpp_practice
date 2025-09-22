cmake_minimum_required(VERSION 3.5)

project(216_namespace_across_multiple_files LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(216_namespace_across_multiple_files main.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/classes/point.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/classes/line.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/classes/cylinder.cpp)


include(GNUInstallDirs)
install(TARGETS 216_namespace_across_multiple_files
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
