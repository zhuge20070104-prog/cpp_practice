cmake_minimum_required(VERSION 3.5)

project(317_non_type_template_parameter LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(317_non_type_template_parameter main.cpp)


include(GNUInstallDirs)
install(TARGETS 317_non_type_template_parameter
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
