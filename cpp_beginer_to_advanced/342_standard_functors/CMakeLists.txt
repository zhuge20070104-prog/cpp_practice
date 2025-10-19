cmake_minimum_required(VERSION 3.5)

project(342_standard_functors LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(342_standard_functors main.cpp)


include(GNUInstallDirs)
install(TARGETS 342_standard_functors
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
