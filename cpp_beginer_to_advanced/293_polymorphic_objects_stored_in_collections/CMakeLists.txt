cmake_minimum_required(VERSION 3.5)

project(293_polymorphic_objects_stored_in_collections LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(293_polymorphic_objects_stored_in_collections main.cpp
    circle.cpp
    oval.cpp
    shape.cpp
)


include(GNUInstallDirs)
install(TARGETS 293_polymorphic_objects_stored_in_collections
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
