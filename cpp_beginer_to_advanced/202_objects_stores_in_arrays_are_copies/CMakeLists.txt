cmake_minimum_required(VERSION 3.5)

project(202_objects_stores_in_arrays_are_copies LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(202_objects_stores_in_arrays_are_copies main.cpp)


include(GNUInstallDirs)
install(TARGETS 202_objects_stores_in_arrays_are_copies
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
