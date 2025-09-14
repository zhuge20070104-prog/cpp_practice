cmake_minimum_required(VERSION 3.5)

project(156_auto_function_templates LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(156_auto_function_templates main.cpp)

include(GNUInstallDirs)
install(TARGETS 156_auto_function_templates
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
