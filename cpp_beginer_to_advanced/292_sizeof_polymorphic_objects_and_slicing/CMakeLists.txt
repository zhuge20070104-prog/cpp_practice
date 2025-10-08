cmake_minimum_required(VERSION 3.5)

project(292_sizeof_polymorphic_objects_and_slicing LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(292_sizeof_polymorphic_objects_and_slicing main.cpp
    circle.cpp
    oval.cpp
    shape.cpp
)


include(GNUInstallDirs)
install(TARGETS 292_sizeof_polymorphic_objects_and_slicing
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
