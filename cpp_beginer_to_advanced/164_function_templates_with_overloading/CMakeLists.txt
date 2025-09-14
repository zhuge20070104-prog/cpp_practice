cmake_minimum_required(VERSION 3.5)

project(164_function_templates_with_overloading LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(164_function_templates_with_overloading main.cpp)

include(GNUInstallDirs)
install(TARGETS 164_function_templates_with_overloading
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
