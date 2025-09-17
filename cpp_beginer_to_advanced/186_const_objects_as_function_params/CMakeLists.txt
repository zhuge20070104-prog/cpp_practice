cmake_minimum_required(VERSION 3.5)

project(186_const_objects_as_function_params LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(186_const_objects_as_function_params main.cpp)


include(GNUInstallDirs)
install(TARGETS 186_const_objects_as_function_params
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
