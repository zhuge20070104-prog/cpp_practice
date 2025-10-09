cmake_minimum_required(VERSION 3.5)

project(294_override LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(294_override main.cpp
    circle.cpp
    oval.cpp
    shape.cpp
)


include(GNUInstallDirs)
install(TARGETS 294_override
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
