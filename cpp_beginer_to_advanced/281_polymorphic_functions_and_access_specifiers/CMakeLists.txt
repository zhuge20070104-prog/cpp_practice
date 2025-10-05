cmake_minimum_required(VERSION 3.5)

project(281_polymorphic_functions_and_access_specifiers LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(281_polymorphic_functions_and_access_specifiers main.cpp
    shape.cpp
    ellipse.cpp)


include(GNUInstallDirs)
install(TARGETS 281_polymorphic_functions_and_access_specifiers
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
