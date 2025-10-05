cmake_minimum_required(VERSION 3.5)

project(276_default_constructors_with_inheritance LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(276_default_constructors_with_inheritance main.cpp)


include(GNUInstallDirs)
install(TARGETS 276_default_constructors_with_inheritance
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
