cmake_minimum_required(VERSION 3.5)

project(235_shared_ptrs_as_func_params_and_return_values LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(235_shared_ptrs_as_func_params_and_return_values main.cpp
    dog.cpp)


include(GNUInstallDirs)
install(TARGETS 235_shared_ptrs_as_func_params_and_return_values
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
