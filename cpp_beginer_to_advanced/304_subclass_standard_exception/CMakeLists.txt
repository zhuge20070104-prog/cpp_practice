cmake_minimum_required(VERSION 3.5)

project(304_subclass_standard_exception LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(304_subclass_standard_exception main.cpp
)


include(GNUInstallDirs)
install(TARGETS 304_subclass_standard_exception
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
