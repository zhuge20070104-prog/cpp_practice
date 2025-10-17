cmake_minimum_required(VERSION 3.5)

project(333_capturing_by_reference LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(333_capturing_by_reference main.cpp)


include(GNUInstallDirs)
install(TARGETS 333_capturing_by_reference
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
