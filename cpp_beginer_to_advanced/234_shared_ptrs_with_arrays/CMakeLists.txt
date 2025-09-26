cmake_minimum_required(VERSION 3.5)

project(234_shared_ptrs_with_arrays LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(234_shared_ptrs_with_arrays main.cpp
    dog.cpp)


include(GNUInstallDirs)
install(TARGETS 234_shared_ptrs_with_arrays
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
