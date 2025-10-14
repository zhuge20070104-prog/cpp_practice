cmake_minimum_required(VERSION 3.5)

project(318_default_value_for_template_params LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(318_default_value_for_template_params main.cpp)


include(GNUInstallDirs)
install(TARGETS 318_default_value_for_template_params
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
