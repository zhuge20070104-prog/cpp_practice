cmake_minimum_required(VERSION 3.5)

project(231_unique_ptrs_and_arrays LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(231_unique_ptrs_and_arrays main.cpp
    dog.cpp)


include(GNUInstallDirs)
install(TARGETS 231_unique_ptrs_and_arrays
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
