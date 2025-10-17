cmake_minimum_required(VERSION 3.5)

project(334_mixing_capturing LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(334_mixing_capturing main.cpp)


include(GNUInstallDirs)
install(TARGETS 334_mixing_capturing
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
