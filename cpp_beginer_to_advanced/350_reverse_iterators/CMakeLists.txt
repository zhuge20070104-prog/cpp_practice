cmake_minimum_required(VERSION 3.5)

project(350_reverse_iterators LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(350_reverse_iterators main.cpp)


include(GNUInstallDirs)
install(TARGETS 350_reverse_iterators
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
