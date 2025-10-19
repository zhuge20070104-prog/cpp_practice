cmake_minimum_required(VERSION 3.5)

project(347_std_array LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(347_std_array main.cpp)


include(GNUInstallDirs)
install(TARGETS 347_std_array
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
