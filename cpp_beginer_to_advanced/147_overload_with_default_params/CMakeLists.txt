cmake_minimum_required(VERSION 3.5)

project(147_overload_with_default_params LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(147_overload_with_default_params main.cpp)

include(GNUInstallDirs)
install(TARGETS 147_overload_with_default_params
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
