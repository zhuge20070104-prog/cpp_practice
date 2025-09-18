cmake_minimum_required(VERSION 3.5)

project(189_dangling_pointers_and_refs_in_objects LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(189_dangling_pointers_and_refs_in_objects main.cpp)


include(GNUInstallDirs)
install(TARGETS 189_dangling_pointers_and_refs_in_objects
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
