cmake_minimum_required(VERSION 3.5)

project(144_overload_with_const_params_by_value LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(144_overload_with_const_params_by_value main.cpp)

include(GNUInstallDirs)
install(TARGETS 144_overload_with_const_params_by_value
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
