cmake_minimum_required(VERSION 3.5)

project(197_default_parameters_for_constructor LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(197_default_parameters_for_constructor main.cpp)


include(GNUInstallDirs)
install(TARGETS 197_default_parameters_for_constructor
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
