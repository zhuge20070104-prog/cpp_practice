cmake_minimum_required(VERSION 3.5)

project(343_functors_with_parameters LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(343_functors_with_parameters main.cpp)


include(GNUInstallDirs)
install(TARGETS 343_functors_with_parameters
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
