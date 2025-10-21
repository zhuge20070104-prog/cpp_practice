cmake_minimum_required(VERSION 3.5)

project(351_const_iterator LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(351_const_iterator main.cpp)


include(GNUInstallDirs)
install(TARGETS 351_const_iterator
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
