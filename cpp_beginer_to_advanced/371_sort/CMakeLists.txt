cmake_minimum_required(VERSION 3.5)

project(371_sort LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(371_sort main.cpp)


include(GNUInstallDirs)
install(TARGETS 371_sort
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
