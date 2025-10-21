cmake_minimum_required(VERSION 3.5)

project(349_traversing_container_subsets LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(349_traversing_container_subsets main.cpp)


include(GNUInstallDirs)
install(TARGETS 349_traversing_container_subsets
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
