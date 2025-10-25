cmake_minimum_required(VERSION 3.5)

project(360_associative_container_map LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(360_associative_container_map main.cpp)


include(GNUInstallDirs)
install(TARGETS 360_associative_container_map
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
