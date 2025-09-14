cmake_minimum_required(VERSION 3.5)

project(162_template_parameters_by_references LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(162_template_parameters_by_references main.cpp)

include(GNUInstallDirs)
install(TARGETS 162_template_parameters_by_references
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
