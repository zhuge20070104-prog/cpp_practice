cmake_minimum_required(VERSION 3.5)

project(206_static_memebers LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(206_static_memebers main.cpp)


include(GNUInstallDirs)
install(TARGETS 206_static_memebers
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
