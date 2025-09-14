cmake_minimum_required(VERSION 3.5)

project(165_function_template_with_multi_parameters LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(165_function_template_with_multi_parameters main.cpp)

include(GNUInstallDirs)
install(TARGETS 165_function_template_with_multi_parameters
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
