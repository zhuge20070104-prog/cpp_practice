cmake_minimum_required(VERSION 3.5)

project(362_unordered_associative_containers LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(362_unordered_associative_containers main.cpp)


include(GNUInstallDirs)
install(TARGETS 362_unordered_associative_containers
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
