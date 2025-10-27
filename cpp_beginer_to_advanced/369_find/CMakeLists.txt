cmake_minimum_required(VERSION 3.5)

project(369_find LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(369_find main.cpp)


include(GNUInstallDirs)
install(TARGETS 369_find
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
