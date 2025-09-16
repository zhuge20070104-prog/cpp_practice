cmake_minimum_required(VERSION 3.5)

project(185_const_objects LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(185_const_objects main.cpp)


include(GNUInstallDirs)
install(TARGETS 185_const_objects
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
