cmake_minimum_required(VERSION 3.5)

project(209_static_constants_pre_cpp17 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(209_static_constants_pre_cpp17 main.cpp)


include(GNUInstallDirs)
install(TARGETS 209_static_constants_pre_cpp17
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
