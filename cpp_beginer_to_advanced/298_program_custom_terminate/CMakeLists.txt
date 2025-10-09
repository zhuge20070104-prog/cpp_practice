cmake_minimum_required(VERSION 3.5)

project(298_program_custom_terminate LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(298_program_custom_terminate main.cpp
)


include(GNUInstallDirs)
install(TARGETS 298_program_custom_terminate
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
