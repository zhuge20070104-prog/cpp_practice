cmake_minimum_required(VERSION 3.5)

project(182_destructors LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(182_destructors main.cpp)


include(GNUInstallDirs)
install(TARGETS 182_destructors
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
