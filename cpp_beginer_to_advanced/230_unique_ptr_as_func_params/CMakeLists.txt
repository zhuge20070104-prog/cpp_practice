cmake_minimum_required(VERSION 3.5)

project(230_unique_ptr_as_func_params LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(230_unique_ptr_as_func_params main.cpp
    dog.cpp
    person.cpp)


include(GNUInstallDirs)
install(TARGETS 230_unique_ptr_as_func_params
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
