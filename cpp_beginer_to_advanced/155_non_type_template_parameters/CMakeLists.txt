cmake_minimum_required(VERSION 3.5)

project(155_non_type_template_parameters LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(155_non_type_template_parameters main.cpp)

include(GNUInstallDirs)
install(TARGETS 155_non_type_template_parameters
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
