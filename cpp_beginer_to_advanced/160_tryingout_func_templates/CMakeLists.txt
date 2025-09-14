cmake_minimum_required(VERSION 3.5)

project(160_tryingout_func_templates LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(160_tryingout_func_templates main.cpp)

include(GNUInstallDirs)
install(TARGETS 160_tryingout_func_templates
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
