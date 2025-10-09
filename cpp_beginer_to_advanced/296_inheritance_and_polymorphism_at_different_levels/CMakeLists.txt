cmake_minimum_required(VERSION 3.5)

project(296_inheritance_and_polymorphism_at_different_levels LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(296_inheritance_and_polymorphism_at_different_levels main.cpp
    stream_insertable.cpp
)


include(GNUInstallDirs)
install(TARGETS 296_inheritance_and_polymorphism_at_different_levels
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
