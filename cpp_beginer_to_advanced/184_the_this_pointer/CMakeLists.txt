cmake_minimum_required(VERSION 3.5)

project(184_the_this_pointer LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(184_the_this_pointer main.cpp)


include(GNUInstallDirs)
install(TARGETS 184_the_this_pointer
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
