cmake_minimum_required(VERSION 3.5)

project(176_your_first_class LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(176_your_first_class main.cpp)

include(GNUInstallDirs)
install(TARGETS 176_your_first_class
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
