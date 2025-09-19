cmake_minimum_required(VERSION 3.5)

project(200_constructor_delegation LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(200_constructor_delegation main.cpp)


include(GNUInstallDirs)
install(TARGETS 200_constructor_delegation
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
