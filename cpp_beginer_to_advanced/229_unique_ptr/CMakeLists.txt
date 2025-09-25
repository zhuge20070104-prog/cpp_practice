cmake_minimum_required(VERSION 3.5)

project(228_forward_declaration LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(228_forward_declaration main.cpp
    dog.cpp)


include(GNUInstallDirs)
install(TARGETS 228_forward_declaration
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
