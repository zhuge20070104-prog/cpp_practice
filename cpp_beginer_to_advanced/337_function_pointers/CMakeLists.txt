cmake_minimum_required(VERSION 3.5)

project(337_function_pointers LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(337_function_pointers main.cpp)


include(GNUInstallDirs)
install(TARGETS 337_function_pointers
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
